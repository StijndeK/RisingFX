/*
  ==============================================================================

    Parameters.h
    Created: 18 Oct 2020 8:57:34pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
// dataclass to hold general variables
class Parameters {
    
public:
    // subvoices
    std::vector<float> subvoiceGains = {-6, -6, -6, -6};
    
    // voices
    float masterPan = 0.5;
    float masterGain = -6;
};
