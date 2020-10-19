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
#include "ParamSetFunctions.h"
#include "Parameters.h"
#include "AdaptableParameterVariable.h"

class Editor : public juce::Component
{
public:
    Editor(TransitionFxAudioProcessor&);
    ~Editor();
    
    // components and valuetrees
    void createSliders (std::vector<Slider*>& sliders_, std::vector<string>& sliderIds_, Slider::SliderStyle style = Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition textBox = Slider::TextBoxBelow);
    void initialiseSlider (Slider* slider, string& sliderId, ScopedPointer <AudioProcessorValueTreeState::SliderAttachment>* sliderTree, Slider::SliderStyle style, Slider::TextEntryBoxPosition textBox);
    
    // normalisable ranges
    NormalisableRange<float> frequencyRange;
    NormalisableRange<float> gainRange;
    NormalisableRange<float> panRange;
    NormalisableRange<float> lengthMsRange;
    NormalisableRange<float> resonanceRange;
    NormalisableRange<float> zeroOneRange;
    
    void setNormalisableRange (NormalisableRange<float>& range, float start_ = 0, float end_ = 1, float interval_ = 0, float skew_ = 1);

    // processor
    TransitionFxAudioProcessor& processor;
private:

};
