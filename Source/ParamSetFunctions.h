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

void setSimpleValue(float& valueToChange, std::atomic<float>& inputValue);
void setVoiceGain(float& valueToChange, std::atomic<float>& inputValue);
void setEnvAttack(std::atomic<float>& inputValue);
void setEnvRelease(std::atomic<float>& inputValue);
