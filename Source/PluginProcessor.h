
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Envelopes.h"
#include "SubVoice.h"
#include <algorithm>
#include "AdapatableParameter.h"
#include "ParamSetFunctions.h"

class TransitionFxAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
        
    //==============================================================================
    // audio parameters
    float masterPan = 0.5;
    float masterGain = -6;
    std::vector<float> voiceGains = {-6, -6, -6, -6};
    
    //==============================================================================
    // DAW values
    double* bpm;
    AudioPlayHead::FrameRateType framerate;
    double* sampleRate;
    int timeSigNum;
    int timeSigDenom;
    double currentPlayheadPosition; // als meervoud van de numerator is zit je op het begin van een maat
    bool isDawPlaying; // alleen wanneer de daw speelt, linken aan begin van een maat
    
    //==============================================================================
    
    // dsp
    enum{
        reverbIndex
    };
    dsp::ProcessorChain <juce::dsp::Reverb> fxChain;
    dsp::Reverb::Parameters reverbParameters;
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients <float>> lowPassFilter;
    
    float lowpassCutoff = 1000;
    float lowpassResonance = 1;
    
    float nullValue = 0;
    
    //==============================================================================
    // trigger button
    int manualTrigger;
    void triggerManualSound(juce::TextButton::ButtonState state);
    
    //==============================================================================
    // valuetree
    AudioProcessorValueTreeState tree;
    
    void parameterChanged(const String & parameterID, float newValue) override;
    
//    void setSimpleValue(float valueToChange, float inputValue);
    
    void initialiseTreeMember(const String & parameterID, NormalisableRange<float> range, float initialValue, float& parameterToAdapt);
    
    std::vector<AdaptableParameter> adaptableParameters;
    
    //==============================================================================
    TransitionFxAudioProcessor();
    ~TransitionFxAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
private:
    // Create Synth
    Synthesiser mySynth;
    
    // create voice
    SynthVoice* myVoice;
    SubVoice* mySubVoice;
    
    // set amount of voices
    const int numVoices = 3;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransitionFxAudioProcessor)
};
