/*
  ==============================================================================

    ReverbComponent.h
    Created: 12 Oct 2020 11:45:45am
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once

#include "Editor.h"

//==============================================================================
/*
*/
class ReverbComponent  : public Editor
{
public:
    ReverbComponent(TransitionFxAudioProcessor&);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::vector<Slider*> sliders;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
