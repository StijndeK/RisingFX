/*
  ==============================================================================

    VoicesEditor.h
    Created: 11 Oct 2020 2:54:16pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "VoiceComponent.h"
#include "Editor.h"

//==============================================================================
/*
*/
class VoicesEditor : public Editor
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
        
    // voices
    std::vector<VoiceComponent*> voices;
    void addVoice();
    void removeVoice(VoiceComponent* voice);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoicesEditor)
};
