/*
  ==============================================================================

    VoiceComponent.h
    Created: 11 Oct 2020 3:24:17pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class VoiceComponent  : public juce::Component
{
public:
    VoiceComponent();
    ~VoiceComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};
