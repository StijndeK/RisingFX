/*
  ==============================================================================

    ParamSetFunctions.h
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

/* functions to link to adaptable parameters */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelopes.h"
#include <vector>
class TransitionFxAudioProcessor;

class ParamSetFunctions {
public:
    static void setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
    static void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
    static void setStepEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
    static void setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
    static void setEnvStepsFrames(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
    static void setEnvStepsBeats(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
};
