/*
  ==============================================================================

    Editor.h
    Created: 14 Oct 2020 3:10:20pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <vector>

class Editor : public juce::Component
{
public:
    Editor(TransitionFxAudioProcessor&);
    ~Editor();
    
    void createSliders (std::vector<Slider*>& sliders_, std::vector<string>& sliderIds_, Slider::SliderStyle style = Slider::SliderStyle::LinearHorizontal);
    void initialiseSlider (Slider* slider, string& sliderId, ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>* sliderTree, Slider::SliderStyle style);

    // processor
    TransitionFxAudioProcessor& processor;
private:

};