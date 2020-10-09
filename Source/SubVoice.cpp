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
    env.setAttackLin(1000);
    env.setReleaseLin(1000);
}

SubVoice::~SubVoice()
{
}

double SubVoice::OscWave ()
{
    // TODO: set frequency to slider value
    
    return env.arLin(osc.sinebuf4(frequency * pow(2.0 , detune)), trigger);
}
