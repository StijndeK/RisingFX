#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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
    const int pluginWidth = 640;

    // processor
    TransitionFxAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransitionFxAudioProcessorEditor)
};
