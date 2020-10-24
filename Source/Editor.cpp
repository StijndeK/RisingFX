/*
  ==============================================================================

    Editor.cpp
    Created: 14 Oct 2020 3:10:20pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "Editor.h"

Editor::Editor(TransitionFxAudioProcessor& p) : processor(p)
{
    setNormalisableRange(frequencyRange, 200, 2000, 1);
    setNormalisableRange(gainRange, -78.0,0.0, 0.01, 2.5);
    setNormalisableRange(panRange, 0, 1, 0.01);
    setNormalisableRange(lengthMsRange, 100, 10000, 1);
    setNormalisableRange(resonanceRange, 1, 5, 0.1);
    setNormalisableRange(zeroOneRange, 0, 1, 0.1);
    setNormalisableRange(detuneRange, -0.5, 0.5, 0.01);
}

Editor::~Editor()
{
}

// give normalisablerange its parameters
void Editor::setNormalisableRange (NormalisableRange<float>& range, float start_, float end_, float interval_, float skew_)
{
    range.start = start_;
    range.end = end_;
    range.interval = interval_;
    range.skew = skew_;
}

// create and initialise an amount of sliders
// set style if another style then horizontallinear is needed
void Editor::createSliders (std::vector<Slider*>& sliders_, std::vector<AudioProcessorValueTreeState::SliderAttachment*>& attachments_, std::vector<string>& sliderIds_, Slider::SliderStyle style, Slider::TextEntryBoxPosition textBox)
{
    for (int slider = 0; slider < sliderIds_.size(); slider++) { // get amount of sliders from amount of provided ids
        sliders_.push_back(new Slider());
        sliders_.back()->setSliderStyle(style);
        sliders_.back()->setTextBoxStyle(textBox, false, 60, 20);
        addAndMakeVisible(sliders_.back());
        
        attachments_.push_back(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, sliderIds_[slider], *sliders_.back()));
    }
}

// called to delete memory allocated for sliders and attachments
void Editor::deleteSliders (std::vector<Slider*>& sliders_, std::vector<AudioProcessorValueTreeState::SliderAttachment*>& attachments_)
{
    for (int slider = 0; slider < sliders_.size(); slider++) {
        delete(attachments_[slider]);
        delete(sliders_[slider]);
    }
}
