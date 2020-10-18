/*
  ==============================================================================

    AdapatableParameter.cpp
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "AdapatableParameter.h"

AdaptableParameter::AdaptableParameter(const String paramId_, float & param_, void (*paramSetFunction_)(float&, std::atomic<float>&))
{
    paramId = paramId_;
    param = &param_;
    paramSetFunction = paramSetFunction_;
    
//    (*paramSetFunction)(0,0);
}

AdaptableParameter::~AdaptableParameter()
{
    
}
