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
    VoiceComponent(TransitionFxAudioProcessor&, int name, std::vector<string>& gainSliderId);
    ~VoiceComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int voiceNumber;
    
private:
    
    std::vector<Slider*> sliders;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};
