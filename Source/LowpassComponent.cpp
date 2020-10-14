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
    NormalisableRange<float> frequencyRange (200, 2000, 1);
    NormalisableRange<float> gainRange (-78.0,0.0, 0.01, 2.5);
    NormalisableRange<float> panRange (-1, 1, 0.01);
    NormalisableRange<float> lengthMsRange (100, 10000, 1);
    NormalisableRange<float> resonanceRange (1, 5, 0.1);
    NormalisableRange<float> zeroOneRange (0, 1, 0.1);
    
    processor.initialiseTreeMember("lowpassCutoffSliderID", frequencyRange, 1000, processor.lowpassCutoff);
    processor.initialiseTreeMember("lowpassResonanceSliderID", resonanceRange, 1, processor.lowpassResonance);
    
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
