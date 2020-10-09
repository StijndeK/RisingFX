
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TransitionFxAudioProcessorEditor::TransitionFxAudioProcessorEditor (TransitionFxAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 500);
    
    // INPUT TYPES
    
    // button
    addAndMakeVisible(toggle);
    toggle.onClick = [this] { updateToggleState (&toggle);   };
    
    // slider
    slider1.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    slider1.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&slider1);
    sliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sliderID", slider1);
    
    // combobox
    box.addItem("1", 1);
    box.addItem("2", 2);
    box.setSelectedId(1);
    box.setJustificationType(Justification::centred);
    box.addListener(this);
    addAndMakeVisible(&box);
    
    // textbox
    addAndMakeVisible(editor);
    editor.setInputRestrictions(2, "0123456789");
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

    g.setColour (Colours::white);
    g.setFont (26.0f);
//    g.drawText ("TRANSITION FX - ALPHA", area, Justification::centredTop);
}

void TransitionFxAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(100).removeFromBottom(100);
    box.setBounds(area.removeFromLeft(area.getWidth() / 4));
    slider1.setBounds(area.removeFromLeft(area.getWidth() / 3));
    toggle.setBounds(area.removeFromLeft(area.getWidth() / 2));
    editor.setBounds(area);
}

//==============================================================================
void TransitionFxAudioProcessorEditor::updateToggleState (Button* button)
{
    // manually trigger a sound
    if (button == &toggle) {
        processor.manualTrigger = 1;
    }
}

void TransitionFxAudioProcessorEditor::sliderValueChanged(Slider *slider)
{

}

void TransitionFxAudioProcessorEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    std::cout << "combo box changed" << std::endl;
}



