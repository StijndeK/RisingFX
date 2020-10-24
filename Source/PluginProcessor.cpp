
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
        // TODO: every voice now uses the same set of envelopes. If the synth should be polyfonic, every voice should have own set of envelopes
        mySynth.addVoice(new SynthVoice(parameters.masterPan, parameters.masterGain, parameters.offset, parameters.subvoiceGains, parameters.subvoiceEnvs, parameters.subvoiceOnOffs));

        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))){
            myVoice->setupProcessor(this);
            myVoice->setSamplerate(getSampleRate());
        }
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
        
    NormalisableRange<float> frequencyRange (200, 2000, 1);
    NormalisableRange<float> gainRange (-78.0,0.0, 0.01, 2.5);
    NormalisableRange<float> panRange (0, 1, 0.01);
    NormalisableRange<float> lengthMsRange (100, 10000, 1);
    NormalisableRange<float> resonanceRange (1, 5, 0.1);
    NormalisableRange<float> zeroOneRange (0, 1, 0.1);
    NormalisableRange<float> detuneRange (-0.5, 0.5, 0.01);
    
    /* initialise tree members */
    
    // master
    initialiseTreeMember("gainSliderID", gainRange, parameters.masterGain, {AdaptableParameter({&parameters.masterGain}, &::setGain)});
    initialiseTreeMember("panSliderID", panRange, parameters.masterPan, {AdaptableParameter({&parameters.masterPan})});
    
    // time
    initialiseTreeMember("releaseSliderID", lengthMsRange, parameters.releaseMs, {AdaptableParameter({&parameters.releaseMs}), AdaptableParameter({&parameters.subvoiceEnvs[0].release, &parameters.subvoiceEnvs[1].release, &parameters.subvoiceEnvs[2].release, &parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    initialiseTreeMember("attackSliderID", lengthMsRange, parameters.attackMs, {AdaptableParameter({&parameters.attackMs}), AdaptableParameter({&parameters.subvoiceEnvs[0].attack, &parameters.subvoiceEnvs[1].attack, &parameters.subvoiceEnvs[2].attack, &parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});

    // TODO: implement other envelope types
    initialiseTreeMember("releaseFramesSliderID", lengthMsRange, parameters.releaseFrames, {AdaptableParameter({&parameters.releaseFrames}), AdaptableParameter({&parameters.subvoiceEnvs[0].release, &parameters.subvoiceEnvs[1].release, &parameters.subvoiceEnvs[2].release, &parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    initialiseTreeMember("attackFramesSliderID", lengthMsRange, parameters.attackFrames, {AdaptableParameter({&parameters.attackFrames}), AdaptableParameter({&parameters.subvoiceEnvs[0].attack, &parameters.subvoiceEnvs[1].attack, &parameters.subvoiceEnvs[2].attack, &parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});
    initialiseTreeMember("releaseBeatsSliderID", lengthMsRange, parameters.releaseMs, {AdaptableParameter({&parameters.releaseMs}), AdaptableParameter({&parameters.subvoiceEnvs[0].release, &parameters.subvoiceEnvs[1].release, &parameters.subvoiceEnvs[2].release, &parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    initialiseTreeMember("attackBeatsSliderID", lengthMsRange, parameters.attackMs, {AdaptableParameter({&parameters.attackMs}), AdaptableParameter({&parameters.subvoiceEnvs[0].attack, &parameters.subvoiceEnvs[1].attack, &parameters.subvoiceEnvs[2].attack, &parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});
    
    // voice editor
    initialiseTreeMember("offsetSliderID", detuneRange, parameters.offset, {AdaptableParameter({&parameters.offset})});
    
    // voice components
    for (int voiceNumber = 0; voiceNumber < 4; voiceNumber++) {
        initialiseTreeMember(parameters.voicesIds[voiceNumber][0], gainRange, parameters.subvoiceGains[voiceNumber], {AdaptableParameter({&parameters.subvoiceGains[voiceNumber]}, &::setGain)});
        initialiseTreeMember(parameters.voicesIds[voiceNumber][1], zeroOneRange, parameters.subvoiceOnOffs[voiceNumber], {AdaptableParameter({&parameters.subvoiceOnOffs[voiceNumber]})}); // create slider to link to onoffbutton to link the onoffbutton to a valuetree
    }
    
    // lowpass
    initialiseTreeMember("lowpassCutoffSliderID", frequencyRange, parameters.lowpassCutoff, {AdaptableParameter({&parameters.lowpassCutoff})});
    initialiseTreeMember("lowpassResonanceSliderID", resonanceRange, parameters.lowpassResonance, {AdaptableParameter({&parameters.lowpassResonance})});
    
    // reverb
    initialiseTreeMember("reverbWetSliderID", zeroOneRange, reverbParameters.wetLevel, {AdaptableParameter({&reverbParameters.wetLevel})});
    initialiseTreeMember("reverbWidthSliderID", zeroOneRange, reverbParameters.width, {AdaptableParameter({&reverbParameters.width})});
    initialiseTreeMember("reverbSizeSliderID", zeroOneRange, reverbParameters.roomSize, {AdaptableParameter({&reverbParameters.roomSize})});
    initialiseTreeMember("reverbDampingSliderID", zeroOneRange, reverbParameters.damping, {AdaptableParameter({&reverbParameters.damping})});
    
    // voice components
    tree.state = ValueTree("gainSliderID");
}

TransitionFxAudioProcessor::~TransitionFxAudioProcessor()
{
}
//==============================================================================
// create and add treemember, add listerener, add adaptableparameter
void TransitionFxAudioProcessor::initialiseTreeMember(const String & parameterID, NormalisableRange<float> range, float initialValue, std::vector<AdaptableParameter> adaptableParameters)
{
    // createAndAddParameter is deprecated as off juce 5.4
    using Parameter = AudioProcessorValueTreeState::Parameter;
    tree.createAndAddParameter (std::make_unique<Parameter> (parameterID, parameterID, parameterID, range, initialValue, nullptr, nullptr));
    tree.addParameterListener(parameterID, this);
        
    adaptableLinks.push_back(AdaptableLink(parameterID, adaptableParameters));
    
    // initialise
    parameterChanged(parameterID, *tree.getRawParameterValue(parameterID));
}


//==============================================================================

void TransitionFxAudioProcessor::parameterChanged(const String & parameterID, float newValue)
{
    for (auto &link: adaptableLinks) {
        if (link.paramId == parameterID) {
            for (auto& adaptableParam: link.adaptableParameters) {
                // TODO: use the newValue var (remove atomic float)
                adaptableParam.paramSetFunction(adaptableParam.var, *tree.getRawParameterValue(parameterID));
            }
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
    // TODO: listeners for DAW info
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

    // render next synth block
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
        
    /* reverb and lowpass */
    
    // set parameters
    reverbParameters.dryLevel = 1 - reverbParameters.wetLevel;
    
    // give parameters to reverb for every sample
    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        // verb
        auto& verb = fxChain.template get<reverbIndex>();
        verb.setParameters(reverbParameters);
        
        // filter
        *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), parameters.lowpassCutoff, parameters.lowpassResonance);
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
    auto state = tree.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void TransitionFxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (xmlOn) {
        std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName (tree.state.getType()))
                tree.replaceState (juce::ValueTree::fromXml (*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TransitionFxAudioProcessor();
}
