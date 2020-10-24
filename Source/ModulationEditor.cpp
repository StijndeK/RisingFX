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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

ModulationEditor::~ModulationEditor()
{
}

void ModulationEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("TimeLinkingEditor", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ModulationEditor::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
