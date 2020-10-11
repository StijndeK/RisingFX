/*
  ==============================================================================

    SubVoice.cpp
    Created: 20 Nov 2018 11:09:30am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "SubVoice.h"

SubVoice::SubVoice(double frequency, double detune)
{
    this->frequency = frequency;
    this->detune = detune;
    
    // envelope parameters in ms
    env.setADSRValue(1000, env.attack, false);
    env.setADSRValue(1000, env.release, false);
}

SubVoice::~SubVoice()
{
}

double SubVoice::oscWave ()
{
    return env.arLin(osc.sinewave(frequency * pow(2.0 , detune)), trigger);
}
