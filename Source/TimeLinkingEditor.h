/*
  ==============================================================================

    TimeLinkingEditor.h
    Created: 11 Oct 2020 2:40:32pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class TimeLinkingEditor  : public Editor
{
public:
    TimeLinkingEditor(TransitionFxAudioProcessor&);
    ~TimeLinkingEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeLinkingEditor)
};
