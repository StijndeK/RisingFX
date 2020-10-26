/*
  ==============================================================================

    AdapatableParameter.cpp
    Created: 12 Oct 2020 3:25:04pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "AdapatableParameter.h"
#include "PluginProcessor.h"

AdaptableLink::AdaptableLink(const String & paramId_, std::vector<AdaptableParameter> adaptableParameters_)
{
    paramId = paramId_;
    adaptableParameters = adaptableParameters_;
}

AdaptableLink::~AdaptableLink()
{
    
}

AdaptableParameter::AdaptableParameter(std::vector<float*> var_, void (*paramSetFunction_)(std::vector<float*>, std::atomic<float>&, TransitionFxAudioProcessor* p))
{
    paramSetFunction = paramSetFunction_;
    var = var_;
}

AdaptableParameter::~AdaptableParameter()
{
    
}
