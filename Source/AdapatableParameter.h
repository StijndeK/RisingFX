/*
  ==============================================================================

    AdapatableParameter.h
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ParamSetFunctions.h"

class AdaptableParameter
{
public:
    AdaptableParameter(const String & paramId_, float & param_, void (*paramSetFunction_)(float&, std::atomic<float>&));
    ~AdaptableParameter();
        
    String paramId;
    float* param;
    void (*paramSetFunction)(float&, std::atomic<float>&);
};
