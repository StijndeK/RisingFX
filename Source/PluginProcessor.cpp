
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TransitionFxAudioProcessor::TransitionFxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif

                       ),
tree (*this, nullptr)       // initialise valuetree
#endif
{
    /* Valuetree */
    
    NormalisableRange<float> frequencyRange (200, 2000, 1);
    NormalisableRange<float> gainRange (-78.0,0.0, 0.01, 2.5);
    NormalisableRange<float> panRange (-1, 1, 0.01);
    NormalisableRange<float> lengthMsRange (100, 10000, 1);
    
    // TODO: create general variable for IDs. ik kan gewoon een aparte class maken anders maken met de ids?
    initialiseTreeMember("sliderID", frequencyRange, 400);
    initialiseTreeMember("gainSliderID", gainRange, -6);
    initialiseTreeMember("panSliderID", panRange, 0);
    initialiseTreeMember("releaseSliderID", lengthMsRange, 1000);
    initialiseTreeMember("attackSliderID", lengthMsRange, 1000);
    
    // initialise
    tree.state = ValueTree("sliderID");

    /* Synthesiser */
    
    // clear old voices
    mySynth.clearVoices();
    // add voices and sounds
    for (int i = 0; i < numVoices; i++) {
        mySynth.addVoice(new SynthVoice);
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
    
    // set samplerate
    if (getSampleRate() != 0){
        mySynth.setCurrentPlaybackSampleRate(getSampleRate());
    }
    else{
        mySynth.setCurrentPlaybackSampleRate(44100);
    }
    

    /* Reverb */

    auto& verb = fxChain.template get<reverbIndex>();
    verb.setParameters(reverbParameters);
}

TransitionFxAudioProcessor::~TransitionFxAudioProcessor()
{
    
}
//==============================================================================
void TransitionFxAudioProcessor::initialiseTreeMember(string id, NormalisableRange<float> range, float initialValue)
{
    tree.createAndAddParameter(id, id, id, range, initialValue, nullptr, nullptr);
    tree.addParameterListener(id, this);
}


//==============================================================================

void TransitionFxAudioProcessor::parameterChanged(const String & parameterID, float newValue)
{
    // if voice is cast as synt voice, relay information (set values from input via valuetreestate class)
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        // check which voice is being edited
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))){
            
            myVoice->getSlider(*tree.getRawParameterValue(parameterID), parameterID);
        }
    }
}

void TransitionFxAudioProcessor::triggerManualSound(juce::TextButton::ButtonState state)
{
    if (state == 2) {
        mySynth.manualTrigger(1);
    }
    else {
        mySynth.manualTrigger(0);
    }
}

//==============================================================================
const String TransitionFxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TransitionFxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TransitionFxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TransitionFxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TransitionFxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TransitionFxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TransitionFxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TransitionFxAudioProcessor::setCurrentProgram (int index)
{
}

const String TransitionFxAudioProcessor::getProgramName (int index)
{
    return {};
}

void TransitionFxAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TransitionFxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    /* DSP initialising */
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    fxChain.reset();
    fxChain.prepare (spec);
}

void TransitionFxAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TransitionFxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

//==============================================================================
// processing
//==============================================================================
void TransitionFxAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    
    // if voice is cast as synt voice, relay information (set values from input via valuetreestate class)
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        // check which voice is being edited
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))){
            
            // link processor in voice
            myVoice->setupProcessor(this);
            
            // get samplerate
            myVoice->setSamplerate(getSampleRate());
        }
    }
    
    // cal proccesor located in Voices
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    /* reverb*/
    
    // set parameters
    reverbParameters.roomSize = 1;
    reverbParameters.wetLevel = 1;
    reverbParameters.dryLevel = 1 - reverbParameters.wetLevel;
    reverbParameters.damping  = 1;
    reverbParameters.width    = 1;
    
    // give parameters to reverb for every sample
    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        auto& verb = fxChain.template get<reverbIndex>();
        verb.setParameters(reverbParameters);
    }

    // set output
    auto verbBlock = juce::dsp::AudioBlock<float> (buffer);
    auto blockToUse = verbBlock.getSubBlock (0, buffer.getNumSamples());
    auto contextToUse = juce::dsp::ProcessContextReplacing<float> (blockToUse);
    fxChain.process(contextToUse);
    
}   // end of processBlock

//==============================================================================
bool TransitionFxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TransitionFxAudioProcessor::createEditor()
{
    return new TransitionFxAudioProcessorEditor (*this);
}

//==============================================================================
void TransitionFxAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void TransitionFxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TransitionFxAudioProcessor();
}
