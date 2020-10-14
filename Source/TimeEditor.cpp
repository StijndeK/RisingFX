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
    string sliderIds [6] = {"attackSliderID", "releaseSliderID", "attackBeatsSliderID", "releaseBeatsSliderID", "attackFramesSliderID", "releaseFramesSliderID"};
    
    // create amount of sliders
    for (int slider = 0; slider < 6; slider++) {
        sliders.push_back(new Slider());
        attachments.push_back(new ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>());
        initialiseSlider(sliders[slider], sliderIds[slider], attachments[slider]);
    }
    
    timeValueBox.addItem("MS", 1);
    timeValueBox.addItem("Beats", 2);
    timeValueBox.addItem("Frames", 3);
    timeValueBox.setSelectedId(1);
    timeValueBox.setJustificationType(Justification::centred);
    timeValueBox.addListener(this);
    addAndMakeVisible(&timeValueBox);
}

TimeEditor::~TimeEditor()
{
}

void TimeEditor::initialiseSlider (Slider* slider, string& sliderId, ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>* sliderTree)
{
    slider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    slider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(slider);
    *sliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, sliderId, *slider);
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
    
    sliders[0]->setBounds(localArea.removeFromLeft(localArea.getWidth()/3));
    sliders[2]->setBounds(sliders[0]->getBounds());
    sliders[4]->setBounds(sliders[0]->getBounds());
    timeValueBox.setBounds(localArea.removeFromLeft(localArea.getWidth()/2).reduced(0, 5));
    sliders[1]->setBounds(localArea.removeFromLeft(localArea.getWidth()));
    sliders[3]->setBounds(sliders[1]->getBounds());
    sliders[5]->setBounds(sliders[1]->getBounds());
}

void TimeEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    // set visible sliders based on what time option is selected
    for (auto &slider: sliders) {
        slider->setVisible(false);
    }
    if (comboBoxThatHasChanged->getSelectedId() == 1) {
        sliders[0]->setVisible(true);
        sliders[1]->setVisible(true);
    }
    if (comboBoxThatHasChanged->getSelectedId() == 2) {
        sliders[2]->setVisible(true);
        sliders[3]->setVisible(true);
    }
    if (comboBoxThatHasChanged->getSelectedId() == 3) {
        sliders[4]->setVisible(true);
        sliders[5]->setVisible(true);
    }
}
