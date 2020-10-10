#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MasterEditor.h"
#include "EffectsEditor.h"

// CALLS ALL VISUALS
class TransitionFxAudioProcessorEditor  : public AudioProcessorEditor, public ComboBox::Listener, public Slider::Listener
{
public:
    TransitionFxAudioProcessorEditor (TransitionFxAudioProcessor&);
    ~TransitionFxAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    void sliderValueChanged(Slider *slider) override;
    void updateToggleState (Button* button);

    void selectGUI();

private:
    // processor
    TransitionFxAudioProcessor& processor;
    
    // input types
    TextButton play { "Play" };
    TextEditor editor;
    Slider slider1;
    ComboBox box;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTree;
    
    // layout
    Rectangle<int> area;
    Rectangle<int> titleArea;
    Rectangle<int> mainArea;
    Rectangle<int> mainAreaSwitch;
    Rectangle<int> generalArea;
    
    // editors
    MasterEditor master;
    EffectsEditor effects;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransitionFxAudioProcessorEditor)
};
