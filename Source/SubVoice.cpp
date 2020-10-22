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

SubVoice::SubVoice(float voiceNumber_, float& frequency_, float& detune_, float* gain_, Envelopes* env_, float* onOff_)
{
    frequency = &frequency_;
    detune = &detune_;
    gain = gain_;
    env = env_;
    voiceNumber = voiceNumber_;
    onOff = onOff_;
}

SubVoice::~SubVoice()
{
}

double SubVoice::oscWave ()
{
    return env->arLin(osc.saw(*frequency * pow(2.0 , (voiceNumber * *detune))), trigger) * *gain;
}
