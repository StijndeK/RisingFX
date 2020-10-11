/*
  ==============================================================================

    TimeEditor.cpp
    Created: 11 Oct 2020 1:48:02pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeEditor.h"

//==============================================================================
TimeEditor::TimeEditor(TransitionFxAudioProcessor& p) : processor(p)
{
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&attackSlider);
    attackSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attackSliderID", attackSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&releaseSlider);
    releaseSliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "releaseSliderID", releaseSlider);
    
    timeValueBox.addItem("MS", 1);
    timeValueBox.addItem("Beats", 2);
    timeValueBox.addItem("Measures", 3);
    timeValueBox.addItem("Frames", 4);
    timeValueBox.addItem("Samples", 5);
    timeValueBox.setSelectedId(1);
    timeValueBox.setJustificationType(Justification::centred);
    timeValueBox.addListener(this);
    addAndMakeVisible(&timeValueBox);
}

TimeEditor::~TimeEditor()
{
}

void TimeEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void TimeEditor::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(5, 10);
    attackSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()/3));
    timeValueBox.setBounds(localArea.removeFromLeft(localArea.getWidth()/2).reduced(0, 5));
    releaseSlider.setBounds(localArea.removeFromLeft(localArea.getWidth()));

}

void TimeEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}
