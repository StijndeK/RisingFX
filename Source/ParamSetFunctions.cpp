/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"
#include "Parameters.h"
#include "PluginProcessor.h"

// TODO: rename valueToChange, because it is also used to pass certain variables necessary
// TODO: link to processor might not be necessary as some variables are passed through valueToChange anyway
// TODO: maybe just use processor reference


void ParamSetFunctions::setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    for (auto& value: valueToChange) {
        *value = pow(10, inputValue / 20);
    }
}

void ParamSetFunctions::setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    for (auto& value: valueToChange) {
        *value = (1.0 / p->getSampleRate()) * (1.0 / (inputValue / 1000.0));
    }
    
    // set the values for every step envelope
    for (string& value: p->parameters.modulationSliderIds[0]) {
        p->parameterChanged(value, *p->tree.getRawParameterValue(value));
    }
}

void ParamSetFunctions::setStepEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p) // first valuetochange is attackAndRelease value to change, second is step value to change and third is the previous step value. Fourth valueToChange is attack or release length .Inputvalue is stepvalue.
{
    // set stepvalue
    *valueToChange[1] = inputValue;
    
    // get difference with previous step to find how much amplitude needs to be increased (should not be 0)
    float amountAmplitude = std::abs(*valueToChange[1] - *valueToChange[2]);
    
    // get entire attack or release length
    float length = *valueToChange[3] / 4;
    
    // calculate attackOrRelease value
    *valueToChange[0] = (amountAmplitude / p->getSampleRate()) * (1.0 / (length / 1000.0));
}

void ParamSetFunctions::setEnvStepsFrames(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p) // last valuetochange is the general length of the attack or ms. All values before are envelope add or subtract values. inputvalue
{
    auto framerate = p->framerate;
    
    // set framerate
    // TODO: listener to adapt framerate when it changes, instead of doing it everything the env step changes
    float usedFramerate;
    switch (framerate) {
        case AudioPlayHead::fps24:
            usedFramerate = 24;
            break;
        case AudioPlayHead::fps25:
            usedFramerate = 25;
            break;
        case AudioPlayHead::fps30:
            usedFramerate = 30;
            break;
        case AudioPlayHead::fps60:
            usedFramerate = 60;
            break;
        case AudioPlayHead::fps2997:
            usedFramerate = 29.97;
            break;
        case AudioPlayHead::fps23976:
            usedFramerate = 23.976;
            break;
        default:
            std::cout << "framerate not found: setting to 24";
            usedFramerate = 120;
            break;
    }
    
    // framerate to ms
    float framesInMs = inputValue / usedFramerate * 1000;
    
    // set general length value
    *valueToChange[valueToChange.size() - 1] = framesInMs;
    
    // set add or subtractvalues
    for (int value = 0; value < valueToChange.size() - 1; value++) {
        *valueToChange[value] = (1.0 / p->getSampleRate()) * (1.0 / (framesInMs / 1000.0));
    }
    
    // set the values for every step envelope
    for (string& value: p->parameters.modulationSliderIds[0]) {
        p->parameterChanged(value, *p->tree.getRawParameterValue(value));
    }
}

void ParamSetFunctions::setEnvStepsBeats(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p) // last valuetochange is the general length of the attack or ms. All values before are envelope add or subtract values
{
    float bpm = (p->bpm == nullptr) ? 100 : *p->bpm;
    
    // beats to ms
    float beatsInMs = 60000.f / bpm * inputValue;

    // set general length value
    *valueToChange[valueToChange.size() - 1] = beatsInMs;

    // set add or subtractvalues
    for (int value = 0; value < valueToChange.size() - 1; value++) {
        *valueToChange[value] = (1.0 / p->getSampleRate()) * (1.0 / (beatsInMs / 1000.0));
    }
    
    // set the values for every step envelope
    for (string& value: p->parameters.modulationSliderIds[0]) {
        p->parameterChanged(value, *p->tree.getRawParameterValue(value));
    }
}

void ParamSetFunctions::setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    for (auto& value: valueToChange) {
        *value = inputValue;
    }
}
