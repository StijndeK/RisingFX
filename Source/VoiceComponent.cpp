/*
  ==============================================================================

    VoiceComponent.cpp
    Created: 11 Oct 2020 3:24:17pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VoiceComponent.h"

//==============================================================================
VoiceComponent::VoiceComponent(TransitionFxAudioProcessor& p, int voiceNumber) : Editor(p)
{
    this->voiceNumber = voiceNumber;
    
    // Buttons
    addAndMakeVisible(removeButton);
}

VoiceComponent::~VoiceComponent()
{
}

void VoiceComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (std::to_string(voiceNumber), getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void VoiceComponent::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(10);
    removeButton.setBounds(localArea.removeFromLeft(20));
}
