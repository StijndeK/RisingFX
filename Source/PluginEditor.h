#pragma once

#include "Editor.h"
#include "MasterEditor.h"
#include "EffectsEditor.h"
#include "TimeEditor.h"
#include "TimeLinkingEditor.h"
#include "VoicesEditor.h"
#include "ModulationEditor.h"

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
    
    // components
    TextButton play { "Play" };
    TextEditor editor;
    ComboBox box;
    ImageComponent logoImage;
        
    // layout
    Rectangle<int> area;
    Rectangle<int> titleArea;
    Rectangle<int> mainArea;
    Rectangle<int> mainAreaVoicesSwitchLength;
    Rectangle<int> mainAreaSwitch;
    Rectangle<int> mainAreaVoices;
    Rectangle<int> generalArea;
    Rectangle<int> lengthArea;
    Rectangle<int> mainAreaModulation;
    // editors
    MasterEditor master;
    EffectsEditor effects;
    TimeEditor time;
    TimeLinkingEditor timeLinking;
    VoicesEditor voices;
    ModulationEditor modulation;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransitionFxAudioProcessorEditor)
};
