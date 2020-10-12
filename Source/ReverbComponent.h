/*
  ==============================================================================

    ReverbComponent.h
    Created: 12 Oct 2020 11:45:45am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(TransitionFxAudioProcessor&);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Slider reverbWetSlider, reverbWidthSlider, reverbSizeSlider, reverbDampingSlider;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbWetSliderTree, reverbWidthSliderTree, reverbSizeSliderTree, reverbDampingSliderTree;
    
    // processor
    TransitionFxAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
