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
    processor.initialiseTreeMember("reverbWetSliderID", zeroOneRange, new AdaptableParameterVariable(processor.reverbParameters.wetLevel));
    processor.initialiseTreeMember("reverbWidthSliderID", zeroOneRange, new AdaptableParameterVariable(processor.reverbParameters.width));
    processor.initialiseTreeMember("reverbSizeSliderID", zeroOneRange, new AdaptableParameterVariable(processor.reverbParameters.roomSize));
    processor.initialiseTreeMember("reverbDampingSliderID", zeroOneRange, new AdaptableParameterVariable(processor.reverbParameters.damping));
    
    std::vector<string> sliderIds = {"reverbWetSliderID", "reverbWidthSliderID", "reverbSizeSliderID", "reverbDampingSliderID"};
    createSliders(sliders, sliderIds, Slider::SliderStyle::RotaryVerticalDrag);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void ReverbComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Rectangle<int> localArea = getLocalBounds().reduced(10);
    for (int i = 0; i < sliders.size(); i ++) {
        sliders[i]->setBounds(localArea.removeFromLeft(localArea.getWidth() / (sliders.size() - i )));
    }
}
