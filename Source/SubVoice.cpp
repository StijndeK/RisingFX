/*
  ==============================================================================

    SubVoice.cpp
    Created: 20 Nov 2018 11:09:30am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "SubVoice.h"

// TODO: link the gain to subvoices
// TODO: subvoice shouldnt have detune, but the subsubvoice, or the osc multiplier should

SubVoice::SubVoice(float& frequency_, float detune_, float* gain_)
{
    frequency = &frequency_;
    detune = detune_;
    gain = gain_;
    
    // envelope parameters in ms
    env.setADSRValue(1000, env.attack, false);
    env.setADSRValue(1000, env.release, false);
}

SubVoice::~SubVoice()
{
}

double SubVoice::oscWave ()
{
//    std::cout << *gain << std::endl;
    return env.arLin(osc.saw(*frequency * pow(2.0 , detune)), trigger) * *gain;
}
