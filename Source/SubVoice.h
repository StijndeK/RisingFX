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
    
public:
    SubVoice(double frequency, double detune);
    ~SubVoice();
    
    double oscWave ();
    
    double detune;
    double frequency;
    
    int trigger = 0;
    
    Envelopes env;
};
