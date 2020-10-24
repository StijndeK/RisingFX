/*
  ==============================================================================

    ModulationEditor.cpp
    Created: 22 Oct 2020 4:15:53pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ModulationEditor.h"


//==============================================================================
ModulationEditor::ModulationEditor(TransitionFxAudioProcessor& p) : Editor(p)
{
    for (int component = 0; component < 2; component ++) {
        // create sliders
        modComponents.push_back(new ModulationComponent(processor, processor.parameters.modulationSliderIds[component]));
        addAndMakeVisible(modComponents.back());
        
        // combobox
        typeBox.addItem(processor.parameters.modulationSliderIds[component][0], component + 1);
    }
    
    typeBox.setSelectedId(1);
    typeBox.setJustificationType(Justification::centred);
    typeBox.addListener(this);
    addAndMakeVisible(&typeBox);
}

ModulationEditor::~ModulationEditor()
{
    for (int x = 0; x < modComponents.size(); x++) {
        delete(modComponents[x]);
    }
}

void ModulationEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void ModulationEditor::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(5);
    typeBox.setBounds(localArea.removeFromTop(20));
    for (auto& component: modComponents) {
        component->setBounds(localArea);
     }
}

void ModulationEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    for (int i = 0; i < modComponents.size(); i++) {
        bool visibility = comboBoxThatHasChanged->getSelectedId() == i + 1; // group by 2 (attack and release) to visible and rest to invisible
        modComponents[i]->setVisible(visibility);
    }
}
