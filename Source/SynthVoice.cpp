/*
  ==============================================================================

    SynthVoiceSource.cpp
    Created: 19 Nov 2018 1:19:31pm
    Author:  Stijn de Koning

  ==============================================================================
*/

class SynthVoice;
#include "PluginEditor.h" // include plugineditor for reference to processor

SynthVoice::SynthVoice()
{
    // create subvoices
    for (int voice = 0; voice < 1; voice++) {
        subVoicesV.push_back(SubVoice(frequency, 0.33 * voice));
    }
}

SynthVoice::~SynthVoice()
{
}

//==============================================================================
//                                Getters
//==============================================================================
void SynthVoice::getSlider (float sliderValue, String ID)
{
    // TODO: optimise. Maybe different getter for subvoices and voices
    if (ID == "sliderID") {
        for (auto &voice : subVoicesV) {
            voice.frequency = sliderValue;
        }
    }
    else if (ID == "gainSliderID") {
        gain = pow(10, sliderValue / 20);   // dbtovolume
    }
    else if (ID == "panSliderID") {
        pan = (sliderValue + 1) / 2; // pan between 0 and 1
    }
    else if (ID == "attackSliderID") {
        for (auto &voice : subVoicesV) {
            voice.env.setADSRValue(sliderValue, voice.env.attack, false);
        }
    }
    else if (ID == "releaseSliderID") {
        for (auto &voice : subVoicesV) {
            voice.env.setADSRValue(sliderValue, voice.env.release, false);
        }
    }
}

//==============================================================================
//                                  Synth
//==============================================================================

// Must return true if this voice object is capable of playing the given sound
bool SynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

// link to processor
void SynthVoice::setupProcessor (TransitionFxAudioProcessor* p)
{
    processor = p;
}

// Called to start a new note.
void SynthVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    amplitude = velocity;
    trigger = 1;
    
    // get frequency from midiNoteNumber
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    
    
    for (auto &voice : subVoicesV) {
        voice.trigger = trigger; // trigger subvoices
        voice.frequency = frequency; // frequency subvoices
    }
}

// Called to stop note
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    allowTailOff = true;
    trigger = 0;
    
    // trigger subvoices
    for (auto &voice : subVoicesV) {
        voice.trigger = trigger;
    }
    
    // clear note after tailoff
    if (amplitude == 0) {
        clearCurrentNote();
    }
}

// Called to let the voice know that the pitch wheel has been moved.
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

// Called to let the voice know that a midi controller has been moved
void SynthVoice::controllerMoved (int controllerNumber, int newControlerValue)
{
}

// set samplerate
void SynthVoice::setSamplerate (float srate)
{
}

//==============================================================================
//                          Processblock, audiocallback
//==============================================================================

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{    
    // per sample
    for (int sample = 0; sample < numSamples; ++sample) {
        
        double theSoundL = 0;
        double theSoundR = 0;
        
        for (auto &voice : subVoicesV) {
            theSoundL = theSoundL + voice.oscWave();
        }
                        
        theSoundL = (theSoundL / (subVoicesV.size() * 2)) * gain;
        theSoundR = theSoundL;
        
        outputBuffer.addSample(0, startSample, theSoundL * (1.0-pan));
        outputBuffer.addSample(1, startSample, theSoundR * pan);

        ++startSample;
    }
}



