
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TransitionFxAudioProcessorEditor::TransitionFxAudioProcessorEditor (TransitionFxAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), master(p), effects(p), time(p)
{
    setSize (800, 500);
    
    // Images
    auto logo = ImageCache::getFromMemory(BinaryData::Logo_png, BinaryData::Logo_pngSize);
    logoImage.setImage(logo, RectanglePlacement::centred);
    addAndMakeVisible(logoImage);
    
    // Editors
    addAndMakeVisible(master);
    addAndMakeVisible(effects);
    addAndMakeVisible(time);
    
    // Buttons
    addAndMakeVisible(play);
    play.onStateChange = [this] { updateToggleState (&play);   };
    
    // Sliders
    slider1.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    slider1.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(&slider1);
    sliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sliderID", slider1);
    
    // Comboboxes
    box.addItem("1", 1);
    box.addItem("2", 2);
    box.setSelectedId(1);
    box.setJustificationType(Justification::centred);
    box.addListener(this);
    addAndMakeVisible(&box);
    
    // Textboxes
    addAndMakeVisible(editor);
    editor.setInputRestrictions(2, "0123456789");
    
    // Areas
    area = getLocalBounds().reduced(20);
    titleArea = getLocalBounds().reduced(20).removeFromTop(40);
    mainArea = getLocalBounds().reduced(20).withTrimmedTop(40).withTrimmedBottom(60).removeFromLeft(500);
    mainAreaSwitch = getLocalBounds().reduced(20).withTrimmedTop(40).removeFromLeft(500).removeFromTop(40);
    lengthArea = getLocalBounds().reduced(20).removeFromBottom(60).removeFromLeft(500);
    generalArea = getLocalBounds().reduced(20).withTrimmedTop(40).removeFromRight(260);
    
    // call resized to set areas (resized is called before constructor)
    resized();
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

//    g.drawRect(area);
//    g.drawRect(titleArea);
    g.drawRect(mainArea);
    g.drawRect(mainAreaSwitch);
    g.drawRect(generalArea);
    g.drawRect(lengthArea);

//    g.drawText ("RFX", titleArea, Justification::centred);
}

void TransitionFxAudioProcessorEditor::resized()
{
    logoImage.setBounds(titleArea);
    play.setBounds(mainAreaSwitch.withTrimmedRight(mainAreaSwitch.getWidth() - 100).reduced(5));
    
    master.setBounds(generalArea.withTrimmedBottom(generalArea.getHeight() / 3 * 2).reduced(10, 5).withTrimmedTop(5));
    effects.setBounds(generalArea.withTrimmedBottom(generalArea.getHeight() / 3).withTrimmedTop(generalArea.getHeight() / 3).reduced(10, 5));
    
    time.setBounds(lengthArea.reduced(5));
    
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
    
}
