/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"
#include "Parameters.h"

// TODO: env setters need a value for what the step per sample is. Solution could be to have the last value of the valuetochange be this value. However, this ofcourse isnt very optimal.
void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue)
{
    float samplerate = 48000;
    for (auto& value: valueToChange) {
        *value = (1.0 / samplerate) * (1.0 / (inputValue / 1000.0));
    }
}

void setEnvStepsFrames(std::vector<float*> valueToChange, std::atomic<float>& inputValue)
{
    float framerate;
    for (auto& value: valueToChange) {
        *value = (1.0 / framerate) * (1.0 / (inputValue / 1000.0));
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

