/*
  ==============================================================================

    LowpassComponent.h
    Created: 12 Oct 2020 11:45:59am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LowpassComponent  : public juce::Component
{
public:
    LowpassComponent(TransitionFxAudioProcessor&);
    ~LowpassComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Slider lowpassCutoffSlider, lowpassResonanceSlider;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> lowpassCutoffSliderTree, lowpassResonanceSliderTree;
    
    // processor
    TransitionFxAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowpassComponent)
};
