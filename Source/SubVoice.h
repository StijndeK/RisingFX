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
        double OscWave ();
        double SubVoiceBlock ();
        double detune;
        double frequency; //TODO: can use the frequency in synthvoice?
};
