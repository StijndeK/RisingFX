/*
  ==============================================================================

    TimeEditor.h
    Created: 11 Oct 2020 1:48:02pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <vector>

//==============================================================================
/*
*/
class TimeEditor  : public juce::Component, public ComboBox::Listener
{
public:
    TimeEditor(TransitionFxAudioProcessor&);
    ~TimeEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

private:
    
    void initialiseSlider (Slider* slider, string& sliderId, ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>* sliderTree);
    
    // components
    std::vector<Slider*> sliders;
    std::vector<ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>*> attachments;

    ComboBox timeValueBox;
    
    // processor
    TransitionFxAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeEditor)
};
