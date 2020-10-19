/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"

void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue)
{
    for (auto& value: valueToChange) {
        *value = (1.0 / 48000) * (1.0 / (inputValue / 1000.0));
    }
}

void setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue)
{
    for (auto& value: valueToChange) {
        *value = pow(10, inputValue / 20);
    }
}

void setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue)
{
    for (auto& value: valueToChange) {
        *value = inputValue;
    }
}
