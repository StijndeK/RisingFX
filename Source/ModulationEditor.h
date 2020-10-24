/*
  ==============================================================================

    ModulationEditor.h
    Created: 22 Oct 2020 4:15:53pm
    Author:  Stijn de Koning

  ==============================================================================
*/
#include "Editor.h"

#pragma once
class ModulationEditor  : public Editor
{
public:
    ModulationEditor(TransitionFxAudioProcessor&);
    ~ModulationEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationEditor)
};
