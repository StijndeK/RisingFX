
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TransitionFxAudioProcessorEditor::TransitionFxAudioProcessorEditor (TransitionFxAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 500);
    
    // INPUT TYPES
    
    // button
    addAndMakeVisible(play);
    play.onStateChange = [this] { updateToggleState (&play);   };
    
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
    
    Rectangle<int> area = getLocalBounds().reduced(20);
    Rectangle<int> titleArea = getLocalBounds().reduced(20).removeFromTop(40);
    Rectangle<int> mainArea = getLocalBounds().reduced(20).withTrimmedTop(40).removeFromLeft(500);
    Rectangle<int> mainAreaSwitch = getLocalBounds().reduced(20).withTrimmedTop(40).removeFromLeft(500).removeFromTop(40);
    Rectangle<int> generalArea = getLocalBounds().reduced(20).withTrimmedTop(40).removeFromRight(260);

    g.drawRect(area);
    g.drawRect(titleArea);
    g.drawRect(mainArea);
    g.drawRect(mainAreaSwitch);
    g.drawRect(generalArea);

    g.drawText ("RFX", titleArea, Justification::centred);
}

void TransitionFxAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(100).removeFromBottom(100);
    box.setBounds(area.removeFromLeft(area.getWidth() / 4));
    slider1.setBounds(area.removeFromLeft(area.getWidth() / 3));
    play.setBounds(area.removeFromLeft(area.getWidth() / 2));
    editor.setBounds(area);
}

//==============================================================================
void TransitionFxAudioProcessorEditor::updateToggleState (Button* button)
{
    // manually trigger a sound
    if (button == &play) {
        processor.triggerManualSound(play.getState());
    }
}

void TransitionFxAudioProcessorEditor::sliderValueChanged(Slider *slider)
{

}

void TransitionFxAudioProcessorEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    std::cout << "combo box changed" << std::endl;
}



