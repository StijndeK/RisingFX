/*
  ==============================================================================

    SubVoice.cpp
    Created: 20 Nov 2018 11:09:30am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "SubVoice.h"

SubVoice::SubVoice(float& frequency_, float detune_)
{
    frequency = &frequency_;
    detune = detune_;
    
    // envelope parameters in ms
    env.setADSRValue(1000, env.attack, false);
    env.setADSRValue(1000, env.release, false);
}

SubVoice::~SubVoice()
{
}

double SubVoice::oscWave ()
{
    return env.arLin(osc.saw(*frequency * pow(2.0 , detune)), trigger);
}
