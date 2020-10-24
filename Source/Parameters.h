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
    /* subvoices */
    std::vector<float> subvoiceGains = {-6, -6, -6, -6};
    std::vector<float> subvoiceOnOffs = {1, 1, 1, 1};
    std::vector<Envelopes> subvoiceEnvs = {Envelopes(), Envelopes(), Envelopes(), Envelopes()};
    std::vector<float> subvoiceAttackLengths = {1000, 1000, 1000, 1000};

    std::vector<std::vector<std::string>> voicesIds = { {"voice1GainSliderId", "voice1OnOffButtonId"},
                                                {"voice2GainSliderId", "voice2OnOffButtonId"},
                                                {"voice3GainSliderId", "voice3OnOffButtonId"},
                                                {"voice4GainSliderId", "voice4OnOffButtonId"} };
    /* voices */
    
    // master
    float masterPan = 0.5;
    float masterGain = -6;
    
    // length
    float attackMs = 1000;
    float releaseMs = 1000;
    float attackFrames = 1000;
    float releaseFrames = 1000;
    float attackBeats = 1000;
    float releaseBeats = 1000;
    
    // DSP
    float lowpassCutoff = 1000;
    float lowpassResonance = 1;
    
    // Voice
    float offset = 0;
    
    /* NOTE: reverbparameters are found in the juce DSP module */
};
