
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
    /* Synthesiser */
    
    // clear old voices
    mySynth.clearVoices();
    // add voices and sounds
    for (int i = 0; i < numVoices; i++) {
        mySynth.addVoice(new SynthVoice(masterPan, masterGain));
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
void TransitionFxAudioProcessor::initialiseTreeMember(const String & parameterID, NormalisableRange<float> range, float initialValue, float& parameterToAdapt)
{
    tree.createAndAddParameter(parameterID, parameterID, parameterID, range, initialValue, nullptr, nullptr);
    tree.addParameterListener(parameterID, this);
    
    // TODO: don't create a copy of the id
    adaptableParameters.push_back(AdaptableParameter(parameterID, parameterToAdapt));
}

//==============================================================================

void TransitionFxAudioProcessor::parameterChanged(const String & parameterID, float newValue)
{
    // TODO: use the same system as is used for processor parameters, for subvoices parameters (find workaround dynamic amount of voices, or create set amount of subvoices beforehand)
    
    // processor parameters
    for (auto &param: adaptableParameters) {
        if (param.paramId == parameterID && param.param != &nullValue) {
            *param.param = *tree.getRawParameterValue(parameterID);
            return; // parameter is in processor, so cast to subvoice is not necessary
        }
    }
    
    // synth and subvoice parameters
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        // check which voice is being edited
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))){
            myVoice->getSlider(*tree.getRawParameterValue(parameterID), parameterID);
        }
    }
}

// send message to synth to start or stop note
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
    
    lowPassFilter.reset();
    lowPassFilter.prepare(spec);
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
    
    // get data from DAW(host)
    // TODO: create listeners
    AudioPlayHead* phead = getPlayHead();
    if (phead != nullptr)           // if there is a host
    {
        AudioPlayHead::CurrentPositionInfo playposinfo;
        phead->getCurrentPosition(playposinfo);
        
        bpm = &playposinfo.bpm;
        framerate = playposinfo.frameRate;
        timeSigNum = playposinfo.timeSigNumerator;
        timeSigDenom = playposinfo.timeSigDenominator;
        currentPlayheadPosition = playposinfo.ppqPosition;
        isDawPlaying = playposinfo.isPlaying;
    }
        
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
        
    /* reverb and lowpass */
    
    // set parameters
    // TODO: allow for multiple parameters to change on listener, so that this value does not have to be calculated every sample
    reverbParameters.dryLevel = 1 - reverbParameters.wetLevel;
    
    // give parameters to reverb for every sample
    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        // verb
        auto& verb = fxChain.template get<reverbIndex>();
        verb.setParameters(reverbParameters);
        
        // filter
        *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), lowpassCutoff, lowpassResonance);
    }

    // set output for reverb
    auto verbBlock = juce::dsp::AudioBlock<float> (buffer);
    auto blockToUse = verbBlock.getSubBlock (0, buffer.getNumSamples());
    auto contextToUse = juce::dsp::ProcessContextReplacing<float> (blockToUse);
    fxChain.process(contextToUse);
    
    // set output for filter
    dsp::AudioBlock<float> block (buffer);
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
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
