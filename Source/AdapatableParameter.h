/*
  ==============================================================================

    AdapatableParameter.h
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdaptableParameterVariable.h"

class AdaptableParameter
{
public:
    AdaptableParameter(const String & paramId_, void (*paramSetFunction_)(AdaptableParameterVariable&, std::atomic<float>&), AdaptableParameterVariable* var_);
    ~AdaptableParameter();
        
    String paramId;
    void (*paramSetFunction)(AdaptableParameterVariable&, std::atomic<float>&);
    AdaptableParameterVariable* var;
};
