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
}

SubVoice::~SubVoice()
{
}

double SubVoice::OscWave ()
{
    return osc.sinebuf4(frequency * pow(2.0 , detune));
}
