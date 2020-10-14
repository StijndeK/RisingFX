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

}

Editor::~Editor()
{
}

// create and initialise an amount of sliders
// set style if another style then horizontallinear is needed
void Editor::createSliders (std::vector<Slider*>& sliders_, std::vector<string>& sliderIds_, Slider::SliderStyle style)
{
    for (int slider = 0; slider < sliderIds_.size(); slider++) { // get amount of sliders from amount of provided ids
        sliders_.push_back(new Slider());
        initialiseSlider(sliders_.back(), sliderIds_[slider], new ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>(), style); // edit the last added slider in the vector, because createsliders should be called more then once when different styles of sliders are to be created
    }
}

// initialise a slider and give it a tree state
void Editor::initialiseSlider (Slider* slider, string& sliderId, ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>* sliderTree, Slider::SliderStyle style)
{
    slider->setSliderStyle(style);
    slider->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(slider);
    *sliderTree = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, sliderId, *slider);
}