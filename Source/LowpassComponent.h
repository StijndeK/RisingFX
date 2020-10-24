/*
  ==============================================================================

    LowpassComponent.h
    Created: 12 Oct 2020 11:45:59am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class LowpassComponent  : public Editor
{
public:
    LowpassComponent(TransitionFxAudioProcessor&);
    ~LowpassComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::vector<Slider*> sliders;
    std::vector<AudioProcessorValueTreeState::SliderAttachment*> attachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowpassComponent)
};
