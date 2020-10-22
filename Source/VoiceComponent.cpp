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

    processor.initialiseTreeMember(sliderIds[0], gainRange, processor.parameters.subvoiceGains[voiceNumber], {AdaptableParameter({&processor.parameters.subvoiceGains[voiceNumber]}, &::setGain)});
    processor.initialiseTreeMember(sliderIds[1], zeroOneRange, processor.parameters.subvoiceOnOffs[voiceNumber], {AdaptableParameter({&processor.parameters.subvoiceOnOffs[voiceNumber]})}); // create slider to link to onoffbutton to link the onoffbutton to a valuetree

    createSliders(sliders, sliderIds, Slider::SliderStyle::LinearVertical, Slider::NoTextBox);
    
    // init buttons
    buttonOnOff(&onOffButton);
}

VoiceComponent::~VoiceComponent()
{
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
    if (button->getState() == 0) {
        
    }
    if (button->getState() == 1) {
        
    }
    if (button->getState() == 2) {
        std::cout << "pressed" << std::endl;
        buttonOnOff(button);
    }
}

void VoiceComponent::buttonOnOff (Button* button)
{
    buttonState = !buttonState;
    if (buttonState) { // on
        button->setColour(TextButton::buttonColourId, juce::Colours::lightslategrey);
        sliders[1]->setValue(1);
    }
    else { // off
        button->setColour(TextButton::buttonColourId, getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        sliders[1]->setValue(0);
    }
}
