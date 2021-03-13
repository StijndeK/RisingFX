/*
  ==============================================================================

    Parameters.h
    Created: 18 Oct 2020 8:57:34pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

//class Parameters2 {
//public:
//    static float masterPan;
//};
//
//float Parameters2::masterPan = 0.5;


// dataclass to hold general variables
struct Parameters {
    
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
    
    std::vector<std::vector<std::string>> modulationSliderIds = { {"gainMod1SliderId", "gainMod2SliderId", "gainMod3SliderId", "gainMod4SliderId", "gainMod5SliderId", "gainMod6SliderId", "gainMod7SliderId", "gainMod8SliderId"},
                                                            {"panMod1SliderId", "panMod2SliderId", "panMod3SliderId", "panMod4SliderId", "panMod5SliderId", "panMod6SliderId", "panMod7SliderId", "panMod8SliderId"} };
    /* voices */
    
    // master
    float masterPan = 0.5;
    float masterGain = -6;
    
    // length
    float attackMs = 1000;
    float releaseMs = 1000;
    float attackFrames = 24;
    float releaseFrames = 24;
    float attackBeats = 4;
    float releaseBeats = 4;
    
    // DSP
    float lowpassCutoff = 1000;
    float lowpassResonance = 1;
    Envelopes gainEnv;
    
    // Voice
    float offset = 0;
    
    /* NOTE: reverbparameters are found in the juce DSP module */
    /* NOTE: envelope parameters are found in the Enevlopes class */
};
