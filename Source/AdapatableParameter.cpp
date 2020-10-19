/*
  ==============================================================================

    AdapatableParameter.cpp
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "AdapatableParameter.h"

AdaptableParameter::AdaptableParameter(const String & paramId_, float & param_, void (*paramSetFunction_)(AdaptableParameterVariable&, std::atomic<float>&), AdaptableParameterVariable* var_)
{
    paramId = paramId_;
    param = &param_;
    paramSetFunction = paramSetFunction_;
    var = var_;
}

AdaptableParameter::~AdaptableParameter()
{
    
}
