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
#include "VoiceComponent.h"
#include <vector>
#include "HeritTest.h"

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
    
    void updateToggleState (Button* button);

private:
    // components
    TextButton addButton { "+" };
    
    // processor
    TransitionFxAudioProcessor& processor;
    
    // voices
    std::vector<VoiceComponent> voices;
    VoiceComponent voice;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoicesEditor)
};
