/*
  ==============================================================================

    LowpassComponent.cpp
    Created: 12 Oct 2020 11:45:59am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LowpassComponent.h"

//==============================================================================
LowpassComponent::LowpassComponent(TransitionFxAudioProcessor& p) : Editor(p)
{
    std::vector<string> sliderIds = {"lowpassCutoffSliderID", "lowpassResonanceSliderID"};
    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::RotaryVerticalDrag);
}

LowpassComponent::~LowpassComponent()
{
    deleteSliders(sliders, attachments);
}

void LowpassComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void LowpassComponent::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(10);
    sliders[0]->setBounds(localArea.removeFromLeft(localArea.getWidth()/2));
    sliders[1]->setBounds(localArea);
}
