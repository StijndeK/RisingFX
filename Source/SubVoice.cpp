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

    env->steps = {0.1, 0.2, 0.3, 1, 0.3, 0.2, 0.1, 0}; // TODO: get these values from input and link with paramsetfunction
    for (int i = 0; i < env->steps.size(); i++) {
        float amountOfTime = std::abs(env->steps[i] - env->steps[i - 1]); // difference
        env->attacksAndReleases.push_back((amountOfTime / 48000) * (1.0 / (1000.0 / 1000.0)));
    }
}

SubVoice::~SubVoice()
{
}

// set which voice type the voice has
// TODO: set reference to function so the function isnt in processing change
void SubVoice::setVoiceType ()
{
//    switch (<#expression#>) {
//        case <#constant#>:
//            <#statements#>
//            break;
//
//        default:
//            break;
//    }
}

double SubVoice::oscWave ()
{
    return env->arLinSteps(osc.saw(*frequency * pow(2.0 , (voiceNumber * *detune))), trigger) * *gain;
}
