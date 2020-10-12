/*
  ==============================================================================

    LowpassComponent.cpp
    Created: 12 Oct 2020 11:45:59am
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LowpassComponent.h"

//==============================================================================
LowpassComponent::LowpassComponent(TransitionFxAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

LowpassComponent::~LowpassComponent()
{
}

void LowpassComponent::paint (juce::Graphics& g)
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
    g.drawText ("LowpassComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void LowpassComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
