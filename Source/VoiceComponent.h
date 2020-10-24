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
    void updateToggleState (Button* button);

    int voiceNumber;
    
    TextButton onOffButton { "Voice _" }; 
private:
    
    std::vector<Slider*> sliders;
    std::vector<AudioProcessorValueTreeState::SliderAttachment*> attachments;
    
    void buttonOnOff (Button* button);
    bool buttonState = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};
