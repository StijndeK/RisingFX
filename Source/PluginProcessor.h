
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Envelopes.h"
#include "SubVoice.h"
#include <algorithm>


class TransitionFxAudioProcessor  : public AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    
    // dsp
    enum{
        reverbIndex
    };
    dsp::ProcessorChain <juce::dsp::Reverb> fxChain;
    dsp::Reverb::Parameters reverbParameters;
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients <float>> lowPassFilter;
    
    //==============================================================================
    // trigger button
    int manualTrigger;
    void triggerManualSound(juce::TextButton::ButtonState state);
    
    //==============================================================================
    // valuetree
    AudioProcessorValueTreeState tree;
    
    void parameterChanged(const String & parameterID, float newValue) override;
    
    void initialiseTreeMember(string id, NormalisableRange<float> range, float initialValue);
    
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
