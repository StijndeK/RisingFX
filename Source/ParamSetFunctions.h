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
#include <vector>

void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue);
void setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue);
void setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue);
