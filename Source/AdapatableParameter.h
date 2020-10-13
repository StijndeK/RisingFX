/*
  ==============================================================================

    AdapatableParameter.h
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class AdaptableParameter
{
public:
    AdaptableParameter(const String paramId_, float & param_);
    ~AdaptableParameter();
    
    String paramId;
    float* param;
};
