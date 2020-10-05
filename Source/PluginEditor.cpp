
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TransitionFxAudioProcessorEditor::TransitionFxAudioProcessorEditor (TransitionFxAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    setSize (pluginWidth, 680);     // 640 bij 740

}


TransitionFxAudioProcessorEditor::~TransitionFxAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void TransitionFxAudioProcessorEditor::paint (Graphics& g)
{
    // set input elemenet colours
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::aqua);

    getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::dimgrey);

    getLookAndFeel().setColour(TextButton::buttonColourId, Colour(25, 25, 30));

    getLookAndFeel().setColour(ComboBox::backgroundColourId, Colour(25, 25, 30));
    getLookAndFeel().setColour(ComboBox::buttonColourId, Colour(25, 25, 30));

    // set background color and text
    g.fillAll (Colours::black);
    Rectangle<int> area = getLocalBounds().removeFromLeft(pluginWidth).reduced(20).withTrimmedTop(10);

    g.setColour (Colours::white);
    g.setFont (26.0f);
    g.drawText ("TRANSITION FX - ALPHA", area, Justification::centredTop);
}

void TransitionFxAudioProcessorEditor::resized()
{

}


//==============================================================================
void TransitionFxAudioProcessorEditor::updateToggleState (Button* button)
{

}

void TransitionFxAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
   
}

void TransitionFxAudioProcessorEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{

}



