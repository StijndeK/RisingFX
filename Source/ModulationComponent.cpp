/*
  ==============================================================================

    ModulationComponent.cpp
    Created: 24 Oct 2020 5:10:03pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ModulationComponent.h"
#include <JuceHeader.h>

//==============================================================================
ModulationComponent::ModulationComponent(TransitionFxAudioProcessor& p, std::vector<string>& sliderIds) : Editor(p)
{
    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::LinearVertical, Slider::NoTextBox);
}

ModulationComponent::~ModulationComponent()
{
    deleteSliders(sliders, attachments);
}

void ModulationComponent::paint (juce::Graphics& g)
{
}

void ModulationComponent::resized()
{
    // draw the sliders
}
