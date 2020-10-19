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
#include "AdaptableParameterVariable.h"


void setVoiceGain(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue);
void setSimpleValue2(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue);
void setAttackLength(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue);
void setReleaseLength(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue);


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

