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
LowpassComponent::LowpassComponent(TransitionFxAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // cutoff (100, 2000), resonance (1, 5)
    lowpassCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    lowpassCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&lowpassCutoffSlider);
    lowpassCutoffSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lowpassCutoffSliderID", lowpassCutoffSlider);
    
    lowpassResonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    lowpassResonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&lowpassResonanceSlider);
    lowpassResonanceSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lowpassResonanceSliderID", lowpassResonanceSlider);
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
    lowpassCutoffSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()/2));
    lowpassResonanceSlider.setBounds(localArea);
}
