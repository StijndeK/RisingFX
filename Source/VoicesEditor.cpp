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
VoicesEditor::VoicesEditor(TransitionFxAudioProcessor& p) : Editor(p)
{
    // create valuetrees for every voice
    
    // create initial voice
    addVoice();
    
    // Buttons
    addAndMakeVisible(addButton);
    addButton.onStateChange = [this] { updateToggleState (&addButton);   };
}

VoicesEditor::~VoicesEditor()
{
}

void VoicesEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void VoicesEditor::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(5);
    
    addButton.setBounds(localArea.removeFromRight(40).reduced(0, 10));
    
    for (auto& voice: voices) {
        voice->setBounds(localArea.removeFromLeft(95));
        localArea.removeFromLeft(10);
    }
}

void VoicesEditor::addVoice()
{
    voices.push_back(new VoiceComponent(processor, voices.size())); // create new voice and its number
    addAndMakeVisible(voices.back());
    
    // TODO: somehow only a listener to the last created button is created
    voices.back()->removeButton.onStateChange = [&] { updateToggleState (&voices.back()->removeButton);   };
    
    resized(); // draw new voice
}

void VoicesEditor::removeVoice(VoiceComponent* voice)
{
    std::cout << "remove voice: " << voice->voiceNumber << std::endl;
    voices.erase(std::remove(voices.begin(), voices.end(), voice), voices.end()); // remove voice from vector
    delete voice;// remove voice
    
    resized(); // remove new voice
}

void VoicesEditor::updateToggleState (Button* button)
{
    if (button->getState() == 2) {
        if (button == &addButton) {
                addVoice();
        }
        else if (button == &voices[voices.size() - 1]->removeButton ) {
                removeVoice(voices[voices.size() - 1]);
        }
    }
}
