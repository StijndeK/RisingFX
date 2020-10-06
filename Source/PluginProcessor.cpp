
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
    //==============================================================================
    // Synthesiser
    //==============================================================================
    
    // clear old voices
    mySynth.clearVoices();
    // add voices
    for (int i = 0; i < numVoices; i++) {
        mySynth.addVoice(new SynthVoice);
    }
    // clear sound
    mySynth.clearSounds();
    // add sounds
    mySynth.addSound(new SynthSound());
    
    // set samplerate
    if (getSampleRate() != 0){
        mySynth.setCurrentPlaybackSampleRate(getSampleRate());
    }
    else{
        mySynth.setCurrentPlaybackSampleRate(44100);
    }
}

TransitionFxAudioProcessor::~TransitionFxAudioProcessor()
{
    
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
    // clear buffer
    buffer.clear();
    
    
    //==============================================================================
    // if voice is cast as synt voice, relay information (set values from input via valuetreestate class)
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        // check which voice is being edited
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))){
            
            // get samplerates
            myVoice->setSamplerate(getSampleRate());
            
            // setup processors in voices
            myVoice->setupProcessor(this);
            
        }
    } // end forloop walktrough voices
    
    
    // cal proccesor located in SyntVoice.h
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
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
//    ScopedPointer<XmlElement> xml (tree.state.createXml());
//    copyXmlToBinary(*xml, destData);
}

void TransitionFxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /*
    if (saveXml == true){
        //get xml from binary
        ScopedPointer<XmlElement> parameters (getXmlFromBinary(data, sizeInBytes));
        //errorcheck
        if (parameters != nullptr){
            if (parameters -> hasTagName(tree.state.getType())){
                tree.state = ValueTree::fromXml(*parameters);
            }
        }
    }
     */
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TransitionFxAudioProcessor();
}
