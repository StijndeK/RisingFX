/*
  ==============================================================================

    VoicesEditor.h
    Created: 11 Oct 2020 2:54:16pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class VoicesEditor  : public juce::Component
{
public:
    VoicesEditor(TransitionFxAudioProcessor&);
    ~VoicesEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // processor
    TransitionFxAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoicesEditor)
};
