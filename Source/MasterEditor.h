/*
  ==============================================================================

    MasterEditor.h
    Created: 10 Oct 2020 12:20:23pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MasterEditor  : public juce::Component
{
public:
    MasterEditor(TransitionFxAudioProcessor&);
    ~MasterEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Slider gainSlider, panSlider;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> gainSliderTree, panSliderTree;
    
    // processor
    TransitionFxAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterEditor)
};
