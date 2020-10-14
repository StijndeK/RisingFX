/*
  ==============================================================================

    EffectsEditor.h
    Created: 10 Oct 2020 3:03:27pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"
#include "LowpassComponent.h"
#include "ReverbComponent.h"

//==============================================================================
/*
*/
class EffectsEditor  : public Editor, public ComboBox::Listener
{
public:
    EffectsEditor(TransitionFxAudioProcessor&);
    ~EffectsEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

private:
    ComboBox typeBox;
    
    // components
    LowpassComponent lowpass;
    ReverbComponent reverb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsEditor)
};
