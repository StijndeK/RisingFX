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
MasterEditor::MasterEditor(TransitionFxAudioProcessor& p) : Editor(p)
{
    std::vector<string> linearSliderIds = {"gainSliderID"};
    std::vector<string> knobSliderIds = {"panSliderID"};
    createSliders(sliders, linearSliderIds);
    createSliders(sliders, knobSliderIds, Slider::SliderStyle::RotaryVerticalDrag);
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
    sliders[0]->setBounds(getLocalBounds().removeFromLeft(getLocalBounds().getWidth()/2).reduced(20));
    sliders[1]->setBounds(getLocalBounds().removeFromRight(getLocalBounds().getWidth()/2).reduced(20));
}
