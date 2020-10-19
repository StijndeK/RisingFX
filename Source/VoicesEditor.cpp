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
    std::vector<std::vector<string>> voicesIds = { {"voice1GainSliderId"},
                                                {"voice2GainSliderId"},
                                                {"voice3GainSliderId"},
                                                {"voice4GainSliderId"} };
    
    // create 4 voices
    for (int voice = 0; voice < 4; voice ++) {
        
        // valuetrees
        for (auto& id: voicesIds[voice]) {
            // gain
            processor.initialiseTreeMember(id, gainRange, processor.parameters.subvoiceGains[voice], {AdaptableParameter({&processor.parameters.subvoiceGains[voice]}, &::setGain)});
        }
        
        // voices
        voices.push_back(new VoiceComponent(processor, voice, voicesIds[voice]));
        addAndMakeVisible(voices.back());
    }
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
    localArea.removeFromLeft(5);
    
//    addButton.setBounds(localArea.removeFromRight(40).reduced(0, 10));
    
    for (auto& voice: voices) {
        voice->setBounds(localArea.removeFromLeft(110));
        localArea.removeFromLeft(10);
    }
}

void VoicesEditor::addVoice()
{

}

void VoicesEditor::removeVoice(VoiceComponent* voice)
{

}

void VoicesEditor::updateToggleState (Button* button)
{
    if (button->getState() == 2) {
//        if (button == &addButton) {
//            addVoice();
//        }
    }
}
