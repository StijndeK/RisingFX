/*
  ==============================================================================

    MasterEditor.cpp
    Created: 10 Oct 2020 12:20:23pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterEditor.h"

//==============================================================================
MasterEditor::MasterEditor(TransitionFxAudioProcessor& p) : processor(p)
{
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&gainSlider);
    gainSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "gainSliderID", gainSlider);
    
    panSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    panSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&panSlider);
    panSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "panSliderID", panSlider);
}

MasterEditor::~MasterEditor()
{
}

void MasterEditor::paint (juce::Graphics& g)
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
    g.drawText ("MasterEditor", getLocalBounds().reduced(10),
                juce::Justification::centredTop, true);   // draw some placeholder text
}

void MasterEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    gainSlider.setBounds(getLocalBounds().removeFromLeft(getLocalBounds().getWidth()/2).reduced(20));
    panSlider.setBounds(getLocalBounds().removeFromRight(getLocalBounds().getWidth()/2).reduced(20));
}
