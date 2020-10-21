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
EffectsEditor::EffectsEditor(TransitionFxAudioProcessor& p) : Editor(p), lowpass(p), reverb(p)
{
    addAndMakeVisible(lowpass);
    addAndMakeVisible(reverb);
    reverb.setVisible(false);
    
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
    lowpass.setBounds(getLocalBounds().withTrimmedTop(20));
    reverb.setBounds(getLocalBounds().withTrimmedTop(20));
}

void EffectsEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged->getSelectedId() == 1) {
        lowpass.setVisible(true);
        reverb.setVisible(false);
    }
    else if (comboBoxThatHasChanged->getSelectedId() == 2) {
        lowpass.setVisible(false);
        reverb.setVisible(true);
    }
}
