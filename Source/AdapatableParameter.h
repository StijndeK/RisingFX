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
    AdaptableParameter(std::vector<float*> var_, void (*paramSetFunction_)(std::vector<float*>, std::atomic<float>&) = &::setSimpleValue);
    ~AdaptableParameter();
        
    void (*paramSetFunction)(std::vector<float*>, std::atomic<float>&);
    std::vector<float*> var;
};


class AdaptableLink
{
public:
    AdaptableLink(const String & paramId_, std::vector<AdaptableParameter> adaptableParameters_);
    ~AdaptableLink();
        
    String paramId;
    std::vector<AdaptableParameter> adaptableParameters;
};


