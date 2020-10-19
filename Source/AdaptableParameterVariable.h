/*
  ==============================================================================

    AdaptableParameterVariable.h
    Created: 19 Oct 2020 11:43:11am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "Envelopes.h"

class AdaptableParameterVariable {
public:
    AdaptableParameterVariable(float& variable_, std::vector<Envelopes>* variableVec_ = nullptr);
    ~AdaptableParameterVariable();
    
    float* variable;
    std::vector<Envelopes>* variableVec;
};
