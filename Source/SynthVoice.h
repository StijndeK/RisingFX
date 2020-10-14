
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"
#include "Envelopes.h"
#include "SubVoice.h"
#include <vector>

class TransitionFxAudioProcessor;

class SynthVoice : public SynthesiserVoice
{
public:
    SynthVoice ();
    ~SynthVoice();

    // synth functions
    bool canPlaySound (SynthesiserSound* sound);
    void setupProcessor (TransitionFxAudioProcessor* p);
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void pitchWheelMoved (int newPitchWheelValue);
    void controllerMoved (int controllerNumber, int newControlerValue);
    void setSamplerate (float srate);
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    
    int trigger;
    
    float frequency = 440;
    
    // get UI data
    void getSlider(float sliderValue, String ID);
    
private:
    // processor
    TransitionFxAudioProcessor *processor;

    // master
    double amplitude;
    // TODO: initialise all input
    double gain = 0.5;
    double pan = 0.5;
    
    maxiOsc osc;
    
    // subvoices
    std::vector<SubVoice> subVoicesV;
};
