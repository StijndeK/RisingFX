/*
  ==============================================================================

    VoiceComponent.h
    Created: 11 Oct 2020 3:24:17pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class VoiceComponent  : public Editor
{
public:
    VoiceComponent(TransitionFxAudioProcessor&, int name);
    ~VoiceComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    int voiceNumber;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};
