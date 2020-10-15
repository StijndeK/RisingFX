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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

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
    voices.push_back(new VoiceComponent(processor, voices.size())); // create new voice and its number (by giving size)
    addAndMakeVisible(voices.back());
    
    // TODO: only last added voice has a listener
    voices.back()->removeButton.onStateChange = [this] { updateToggleState (&voices.back()->removeButton);   }; // add listener
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
        else {
            for (auto& voice: voices) {
                if (button == &voice->removeButton) {
                    std::cout << "togglestate remove voice: " << voice->voiceNumber << std::endl;
                    removeVoice(voice);
                }
            }
        }
    }
}
