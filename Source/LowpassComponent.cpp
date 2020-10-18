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
    processor.initialiseTreeMember("lowpassCutoffSliderID", frequencyRange, processor.parameters.lowpassCutoff);
    processor.initialiseTreeMember("lowpassResonanceSliderID", resonanceRange, processor.parameters.lowpassResonance);
    
    std::vector<string> sliderIds = {"lowpassCutoffSliderID", "lowpassResonanceSliderID"};
    createSliders(sliders, sliderIds, Slider::SliderStyle::RotaryVerticalDrag);
}

LowpassComponent::~LowpassComponent()
{
}

void LowpassComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

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
