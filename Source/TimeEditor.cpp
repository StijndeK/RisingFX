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
    processor.initialiseTreeMember("releaseSliderID", lengthMsRange, processor.parameters.releaseMs, {AdaptableParameter({&processor.parameters.releaseMs}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].release, &processor.parameters.subvoiceEnvs[1].release, &processor.parameters.subvoiceEnvs[2].release, &processor.parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    processor.initialiseTreeMember("attackSliderID", lengthMsRange, processor.parameters.attackMs, {AdaptableParameter({&processor.parameters.attackMs}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].attack, &processor.parameters.subvoiceEnvs[1].attack, &processor.parameters.subvoiceEnvs[2].attack, &processor.parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});
    
    // TODO: implement other envelope types
    processor.initialiseTreeMember("releaseFramesSliderID", lengthMsRange, processor.parameters.releaseFrames, {AdaptableParameter({&processor.parameters.releaseFrames}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].release, &processor.parameters.subvoiceEnvs[1].release, &processor.parameters.subvoiceEnvs[2].release, &processor.parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    processor.initialiseTreeMember("attackFramesSliderID", lengthMsRange, processor.parameters.attackFrames, {AdaptableParameter({&processor.parameters.attackFrames}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].attack, &processor.parameters.subvoiceEnvs[1].attack, &processor.parameters.subvoiceEnvs[2].attack, &processor.parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});
    processor.initialiseTreeMember("releaseBeatsSliderID", lengthMsRange, processor.parameters.releaseMs, {AdaptableParameter({&processor.parameters.releaseMs}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].release, &processor.parameters.subvoiceEnvs[1].release, &processor.parameters.subvoiceEnvs[2].release, &processor.parameters.subvoiceEnvs[3].release}, &::setEnvSteps)});
    processor.initialiseTreeMember("attackBeatsSliderID", lengthMsRange, processor.parameters.attackMs, {AdaptableParameter({&processor.parameters.attackMs}), AdaptableParameter({&processor.parameters.subvoiceEnvs[0].attack, &processor.parameters.subvoiceEnvs[1].attack, &processor.parameters.subvoiceEnvs[2].attack, &processor.parameters.subvoiceEnvs[3].attack}, &::setEnvSteps)});

    
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
