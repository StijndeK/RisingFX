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

void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
void setStepEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
void setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
void setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
void setEnvStepsFrames(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
void setEnvStepsBeats(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p);
