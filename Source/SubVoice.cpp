/*
  ==============================================================================

    SubVoice.cpp
    Created: 20 Nov 2018 11:09:30am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "SubVoice.h"

double SubVoice::OscWave ()
{
    return osc.sinebuf4(frequency * pow(2.0 , detune));
}
