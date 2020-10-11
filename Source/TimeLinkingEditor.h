/*
  ==============================================================================

    TimeLinkingEditor.h
    Created: 11 Oct 2020 2:40:32pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class TimeLinkingEditor  : public juce::Component
{
public:
    TimeLinkingEditor(TransitionFxAudioProcessor&);
    ~TimeLinkingEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    // processor
    TransitionFxAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeLinkingEditor)
};
