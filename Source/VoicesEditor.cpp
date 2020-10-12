/*
  ==============================================================================

    VoicesEditor.cpp
    Created: 11 Oct 2020 2:54:16pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VoicesEditor.h"

//==============================================================================
VoicesEditor::VoicesEditor(TransitionFxAudioProcessor& p) : processor(p), voice()
{
    // Buttons
    addAndMakeVisible(addButton);
    addButton.onStateChange = [this] { updateToggleState (&addButton);   };
    
//    auto test = voice;
    // Start with one voice
//    voices.push_back(voice);
    resized();
}

VoicesEditor::~VoicesEditor()
{
}

void VoicesEditor::paint (juce::Graphics& g)
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
    g.drawText ("VoicesEditor", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void VoicesEditor::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(5);
    
    addButton.setBounds(localArea.removeFromRight(40).reduced(0, 10));
    
//    for (int voice = 0; voice < voices.size(); voice++) {
//        voices[voice].setBounds(localArea.removeFromLeft(40));
//    }
}

void VoicesEditor::updateToggleState (Button* button)
{
    // add new voice component (push back in a vector). when a voice is added, create a new one by addind it to the vector and putting it into resized
//    voices.push_back(VoiceComponent());
}
