/*
  ==============================================================================

    ModulationEditor.h
    Created: 22 Oct 2020 4:15:53pm
    Author:  Stijn de Koning

  ==============================================================================
*/
#include "Editor.h"
#include "ModulationComponent.h"

#pragma once
class ModulationEditor  : public Editor, public ComboBox::Listener
{
public:
    ModulationEditor(TransitionFxAudioProcessor&);
    ~ModulationEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    
private:
    ComboBox typeBox;
    
    std::vector<ModulationComponent*> modComponents;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationEditor)
};
