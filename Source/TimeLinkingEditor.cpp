/*
  ==============================================================================

    TimeLinkingEditor.cpp
    Created: 11 Oct 2020 2:40:32pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TimeLinkingEditor.h"

//==============================================================================
TimeLinkingEditor::TimeLinkingEditor(TransitionFxAudioProcessor& p) : Editor(p)
{
    
}

TimeLinkingEditor::~TimeLinkingEditor()
{
}

void TimeLinkingEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("TimeLinkingEditor", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void TimeLinkingEditor::resized()
{

}
