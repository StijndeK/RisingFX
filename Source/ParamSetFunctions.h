/*
  ==============================================================================

    ParamSetFunctions.h
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

/* functions to link to adaptable parameters */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelopes.h"


    void setSimpleValue(float& valueToChange, std::atomic<float>& inputValue);
    void setVoiceGain(float& valueToChange, std::atomic<float>& inputValue);

    template <typename T> void setAttackLength(T& valueToChange, std::atomic<float>& inputValue) {
            for (auto& env: valueToChange) {
                env.setADSRValue(inputValue, env.attack, false);
            }
    }

    template <typename T> void setReleaseLength(T& valueToChange, std::atomic<float>& inputValue) {
            for (auto& env: valueToChange) {
                env.setADSRValue(inputValue, env.release, false);
            }
    }

