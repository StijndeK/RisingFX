/*
  ==============================================================================

    TimeEditor.h
    Created: 11 Oct 2020 1:48:02pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class TimeEditor  : public Editor, public ComboBox::Listener
{
public:
    TimeEditor(TransitionFxAudioProcessor&);
    ~TimeEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

private:
    std::vector<Slider*> sliders;
    
    ComboBox timeValueBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeEditor)
};
