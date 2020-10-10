/*
  ==============================================================================

    EffectsEditor.cpp
    Created: 10 Oct 2020 3:03:27pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectsEditor.h"

//==============================================================================
EffectsEditor::EffectsEditor(TransitionFxAudioProcessor& p) : processor(p)
{
    // combobox
    typeBox.addItem("Lowpass", 1);
    typeBox.addItem("Reverb", 2);
    typeBox.setSelectedId(1);
    typeBox.setJustificationType(Justification::centred);
    typeBox.addListener(this);
    addAndMakeVisible(&typeBox);
}

EffectsEditor::~EffectsEditor()
{
}

void EffectsEditor::paint (juce::Graphics& g)
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
    g.drawText ("EffectsEditor", getLocalBounds(),
                juce::Justification::centredTop, true);   // draw some placeholder text
}

void EffectsEditor::resized()
{
    typeBox.setBounds(getLocalBounds().removeFromTop(20));
}

void EffectsEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    
}
