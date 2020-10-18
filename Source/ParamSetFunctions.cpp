/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"

// used to set values that do not need any additional calculations
void setSimpleValue(float& valueToChange, std::atomic<float>& inputValue)
{
    valueToChange = inputValue;
}
