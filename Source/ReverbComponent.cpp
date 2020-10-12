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
ReverbComponent::ReverbComponent(TransitionFxAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // wetdry, damping, roomsize, width (all 0, 1)
    reverbWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&reverbWetSlider);
    reverbWetSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbWetSliderID", reverbWetSlider);
    
    reverbWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&reverbWidthSlider);
    reverbWidthSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbWidthSliderID", reverbWidthSlider);
    
    reverbSizeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&reverbSizeSlider);
    reverbSizeSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbSizeSliderID", reverbSizeSlider);
    
    reverbDampingSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    reverbDampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&reverbDampingSlider);
    reverbDampingSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "reverbDampingSliderID", reverbDampingSlider);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("ReverbComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ReverbComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Rectangle<int> localArea = getLocalBounds().reduced(10);
    reverbWetSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()/4));
    reverbWidthSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()/3));
    reverbSizeSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()/2));
    reverbDampingSlider.setBounds(localArea);
}
