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
TimeEditor::TimeEditor(TransitionFxAudioProcessor& p) : Editor(p)
{
    processor.initialiseTreeMember("releaseSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.releaseMs, &processor.parameters.subvoiceEnvs), &::setReleaseLength);
    processor.initialiseTreeMember("attackSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.attackMs, &processor.parameters.subvoiceEnvs), &::setAttackLength);
    processor.initialiseTreeMember("releaseFramesSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.releaseFrames, &processor.parameters.subvoiceEnvs), &::setReleaseLength);
    processor.initialiseTreeMember("attackFramesSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.attackFrames, &processor.parameters.subvoiceEnvs), &::setAttackLength);
    processor.initialiseTreeMember("releaseBeatsSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.releaseBeats, &processor.parameters.subvoiceEnvs), &::setReleaseLength);
    processor.initialiseTreeMember("attackBeatsSliderID", lengthMsRange, new AdaptableParameterVariable(processor.parameters.attackBeats, &processor.parameters.subvoiceEnvs), &::setAttackLength);
    
    std::vector<string> sliderIds = {"attackSliderID", "releaseSliderID", "attackBeatsSliderID", "releaseBeatsSliderID", "attackFramesSliderID", "releaseFramesSliderID"};
    createSliders(sliders, sliderIds);
        
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

void TimeEditor::paint (juce::Graphics& g)
{

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
    for (int i = 0; i < 6; i++) {
        bool visibility = comboBoxThatHasChanged->getSelectedId() == i / 2 + 1; // group by 2 (attack and release) to visible and rest to invisible
        sliders[i]->setVisible(visibility);
    }
}
