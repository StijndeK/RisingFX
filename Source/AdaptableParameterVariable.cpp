/*
  ==============================================================================

    AdaptableParameterVariable.cpp
    Created: 19 Oct 2020 11:43:11am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "AdaptableParameterVariable.h"

AdaptableParameterVariable::AdaptableParameterVariable(float& variable_, std::vector<Envelopes>* variableVec_)
{
    variable = &variable_;
    variableVec = variableVec_;
}

AdaptableParameterVariable::~AdaptableParameterVariable()
{
    
}
