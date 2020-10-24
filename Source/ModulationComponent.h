/*
  ==============================================================================

    ModulationComponent.h
    Created: 24 Oct 2020 5:10:03pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "Editor.h"

class ModulationComponent  : public Editor
{
public:
    ModulationComponent(TransitionFxAudioProcessor&, std::vector<string>& sliderIds);
    ~ModulationComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    std::vector<Slider*> sliders;
    std::vector<AudioProcessorValueTreeState::SliderAttachment*> attachments;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationComponent)
};
