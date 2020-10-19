/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"

// TODO: allow multiple adaptableparameters to be linked to a valuetree, so that there is no need for the AdaptableParameterVariable. The envelope length could be set with a setSimpleVariable and the steplength for within the envelope could be set by linking the [envelope].attack

// used to set values that do not need any additional calculations
void setSimpleValue2(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue)
{
    *valueToChange.variable = inputValue;
}

void setVoiceGain(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue)
{
    *valueToChange.variable =     pow(10, inputValue / 20);
}

void setAttackLength(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue)
{
    // set the variable to its new value
    *valueToChange.variable = inputValue;
    
    // calculate length for all envs
    for (auto& env: *valueToChange.variableVec) {
        env.setADSRValue(inputValue, env.attack, false);
    }
}

void setReleaseLength(AdaptableParameterVariable& valueToChange, std::atomic<float>& inputValue)
{
    // set the variable to its new value
    *valueToChange.variable = inputValue;
    
    // calculate length for all envs
    for (auto& env: *valueToChange.variableVec) {
        env.setADSRValue(inputValue, env.release, false);
    }
}
