
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
#include "Parameters.h"

class TransitionFxAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    float TEMPVALUE;
    
    bool xmlOn = false;
    
    //==============================================================================
    // audio parameters
    Parameters parameters;
    
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
    
    //==============================================================================
    // trigger button
    int manualTrifgger;
    void triggerManualSound(juce::TextButton::ButtonState state);
    
    //==============================================================================
    // valuetree
    AudioProcessorValueTreeState tree;
    
    void parameterChanged(const String & parameterID, float newValue) override;
        
    void initialiseTreeMember(const String & parameterID, NormalisableRange<float> range, float initialValue, std::vector<AdaptableParameter> adaptableParameters);

    
    std::vector<AdaptableParameter> adaptableParameters;
    std::vector<AdaptableLink> adaptableLinks;
    
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
    const int numVoices = 1;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransitionFxAudioProcessor)
};
