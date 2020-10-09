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
    for (int voice = 0; voice < 3; voice++) {
        subVoicesV.push_back(SubVoice(frequency, 0.33 * voice));
    }
}

SynthVoice::~SynthVoice()
{
}

//==============================================================================
//                              Getters
//==============================================================================
void SynthVoice::getSlider (float sliderValue)
{
    
}

//==============================================================================
//                              Synth Functions
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
    
    // trigger subvoices
    // TODO: do this more simple using pointer to trigger
    for (int voice = 0; voice < 3; voice++) {
        subVoicesV[voice].trigger = trigger;
    }
    
    // get frequency from midiNoteNumber
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

// Called to stop note
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    allowTailOff = true;
    trigger = 0;
    
    // trigger subvoices
    // TODO: do this more simple using pointer to trigger
    for (int voice = 0; voice < 3; voice++) {
        subVoicesV[voice].trigger = trigger;
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
        
        double theSoundL;
        
        for (int voice = 0; voice < subVoicesV.size(); voice++) {
            theSoundL = theSoundL + subVoicesV[voice].OscWave(); 
        }
        
        double volume = 0.1;
        
        theSoundL = (theSoundL / subVoicesV.size()) * volume; // TODO: remove 6db per subvoice instead of dividing by size
        
        outputBuffer.addSample(0, startSample, theSoundL);
//        outputBuffer.addSample(1, startSample, theSoundR);

        ++startSample;
    }
}



