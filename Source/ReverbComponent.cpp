/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 12 Oct 2020 11:45:45am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(TransitionFxAudioProcessor& p) : Editor(p)
{
    std::vector<string> sliderIds = {"reverbWetSliderID", "reverbWidthSliderID", "reverbSizeSliderID", "reverbDampingSliderID"};
    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::RotaryVerticalDrag);
}

ReverbComponent::~ReverbComponent()
{
    deleteSliders(sliders, attachments);
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ReverbComponent::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(10);
    for (int i = 0; i < sliders.size(); i ++) {
        sliders[i]->setBounds(localArea.removeFromLeft(localArea.getWidth() / (sliders.size() - i )));
    }
}
