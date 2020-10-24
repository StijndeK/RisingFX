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
VoiceComponent::VoiceComponent(TransitionFxAudioProcessor& p, int voiceNumber, std::vector<string>& sliderIds) : Editor(p)
{
    this->voiceNumber = voiceNumber;
    
    onOffButton.setButtonText(String(voiceNumber));
    onOffButton.onStateChange = [this] { updateToggleState (&onOffButton);   };
    addAndMakeVisible(onOffButton);

    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::LinearVertical, Slider::NoTextBox);
    
    // init buttons
    buttonState = (sliders[1]->getValue() == 1.0) ? true : false;
    buttonOnOff(&onOffButton);
}

VoiceComponent::~VoiceComponent()
{
    deleteSliders(sliders, attachments);
}

void VoiceComponent::paint (juce::Graphics& g)
{
}

void VoiceComponent::resized()
{
    Rectangle<int> localArea = getLocalBounds().reduced(1);
    sliders[0]->setBounds(localArea.removeFromLeft(20));
    onOffButton.setBounds(getLocalBounds());
}

void VoiceComponent::updateToggleState (Button* button)
{
    // if the button is pressed set it to button normal (slider 0) or button down (slider 1) (0 and 2)
    if (button->getState() == 2) {
        buttonOnOff(button);
    }
}

void VoiceComponent::buttonOnOff (Button* button)
{
    if (buttonState) { // on
        button->setColour(TextButton::buttonColourId, juce::Colours::lightslategrey);
        sliders[1]->setValue(1);
    }
    else { // off
        button->setColour(TextButton::buttonColourId, getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        sliders[1]->setValue(0);
    }
    buttonState = !buttonState;
}
