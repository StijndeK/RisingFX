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
    env.setADSRValue(4000, env.attack, true);
    env.setADSRValue(1000, env.release, true);
    
    std::cout << env.attack << std::endl;
    std::cout << env.release << std::endl;
}

SubVoice::~SubVoice()
{
}

double SubVoice::OscWave ()
{
    return env.arExp(osc.sinebuf4(frequency * pow(2.0 , detune)), trigger);
}
