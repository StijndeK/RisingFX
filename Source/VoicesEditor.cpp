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
    std::vector<std::vector<string>> voicesIds = { {"voice1GainSliderId", "voice1OnOffButtonId"},
                                                {"voice2GainSliderId", "voice2OnOffButtonId"},
                                                {"voice3GainSliderId", "voice3OnOffButtonId"},
                                                {"voice4GainSliderId", "voice4OnOffButtonId"} };
    
    // create 4 voices
    for (int voice = 0; voice < 4; voice ++) {
        // voices
        voices.push_back(new VoiceComponent(processor, voice, voicesIds[voice]));
        addAndMakeVisible(voices.back());
    }
    
    // subvoice offset slider    
    std::vector<string> sliderIds = {"offsetSliderID"};
    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::RotaryVerticalDrag, Slider::NoTextBox);
}

VoicesEditor::~VoicesEditor()
{
    deleteSliders(sliders, attachments);
    for (int x = 0; x < voices.size(); x++) {
        delete(voices[x]);
    }
}

void VoicesEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    // slidertitle
    g.setColour (juce::Colours::white);
    g.setFont (12.0f);
    g.drawText ("Offset", getLocalBounds().reduced(5).withTrimmedLeft(425),
                juce::Justification::centredTop, true);
}

void VoicesEditor::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(5);
    localArea.removeFromLeft(5);
        
    for (auto& voice: voices) {
        voice->setBounds(localArea.removeFromLeft(95));
        localArea.removeFromLeft(10);
    }
    
    sliders[0]->setBounds(localArea.withTrimmedTop(10));
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

    }
}
