/*
  ==============================================================================

    MasterEditor.h
    Created: 10 Oct 2020 12:20:23pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class MasterEditor  : public Editor
{
public:
    MasterEditor(TransitionFxAudioProcessor&);
    ~MasterEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::vector<Slider*> sliders;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterEditor)
};
