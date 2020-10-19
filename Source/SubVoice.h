/*
  ==============================================================================

    SubVoice.h
    Created: 20 Nov 2018 11:09:30am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "maximilian.h"
#include "Envelopes.h"
#include "DSP.h"

class SubVoice {
private:
    maxiOsc osc;
    
    float* gain;
    Envelopes* env;
    
public:
    SubVoice(float& frequency_, float detune_, float* gain_, Envelopes* env_);
    ~SubVoice();
    
    double oscWave ();
    
    float detune;
    float* frequency;
    
    int trigger = 0;
    
    Envelopes envLocal;
};
