# RFX
 
RFX is a synthesiser instrument for designing transitional moving effects such as Whooshes, Risers and Stingers. I find there to be a lack of a intuitive synthesisers optimalised for creating these effects, which is why I started developing Transition FX. The user should be able to create the entire sound from within the plugin, without external effects or automation.

RFX is written in C++ using the JUCE framework and [Maximilian DSP](https://github.com/micknoise/Maximilian) library. It is a refactor of the [TransitionFX ALPHA](https://github.com/StijndeK/TransitionFX-ALPHA), made for [Code With Friends Fall 2020](https://codewithfriends.io/events/cwf-fall-2020/).


## Design
Emphesis has been put on not overwelming the user with to many possibilities. It should be easy to make an impressive sounding riser quickly, without any form of manual. Voices containing preset synthesis can be added or removed and given a type and effects can be loaded in and edited. Most control is provided in the modulation. 

Some of the most important elements of Risers  are:
- **A LOT of modulation**: the largest part of the plugin is a modulation editor
- **Length**: the attack and release length can be individually edited based on milliseconds, beats or frames (usefull when working with film)
- **Linking to context**: whether RiserFx is used for a visual medium or within a music track, it is important to be able to link the audio very precisly. *Beat Linking* allows the user to set the impact point, to then be able to edit attack and release, instead of having to move the midi everytime they want to change attack or release length

The design has been based of existing (mostly sample based) plugins such as: [GRAVITY](https://heavyocity.com/product/gravity/), [Whoosh](https://tonsturm.com/software/whoosh/) and [Rise & Hit](https://www.native-instruments.com/en/products/komplete/cinematic/rise-hit/). Air Music's; [The Riser](https://www.airmusictech.com/product/the-riser), was the only synthesis based plugin that I could find and provided a lot of insight in how to create heavy impact with limited input.

## Development

Processor with voices that have subvoices. Input from midi as well as GUI of the plugin.

- picture voices

Made as dynamically as possible, to easily be able to add and change elements. However, because of some limitations with the JUCE framework as well as wanting to keep it simple for a montlong codejam the amount of voices are hardcoded. 


### Linking UI to parameters
Parameter gets linked to voice in constructor, and to user input from initialiseTreeMember, called from the specific components editors constructor using adaptable links containing adaptable parameters. Functions for how the input should adapt a value are nonmember so they can easily be passed as a function argument.
So: processor, voice and subvoice have pointers to processor.parameters. These parameters are held in adaptableparameters which are held in adaptablelinks and callled on by processor.parameterchanged()
using ids to check for everything

- pictures

Just call 2 functions and all done. This system make variable, editor and sliders (fill in 2 functions in component editor) and give variable to the processor, voice or subvoice constructor. And nothing more needs to be done. Very efficient. Instead of needing a giant if statement hardcoded with every type of variable and having to link it to its parameter and therefore also needing more variables. 
example with voice gain and pan(only one adaptable param, gain not using default function):
```C++
processor.initialiseTreeMember("gainSliderID", gainRange, processor.parameters.masterGain, {AdaptableParameter({&processor.parameters.masterGain}, &::setGain)});
processor.initialiseTreeMember("panSliderID", panRange, processor.parameters.masterPan, {AdaptableParameter({&processor.parameters.masterPan})});

createSliders(sliders, linearSliderIds);
```
Editor base class contains functions to create sliders. Header:
```C++
    void createSliders (std::vector<Slider*>& sliders_, std::vector<string>& sliderIds_, Slider::SliderStyle style = Slider::SliderStyle::LinearHorizontal, Slider::TextEntryBoxPosition textBox = Slider::TextBoxBelow);
}
```

if a parameter is changed:
```C++
    for (auto &link: adaptableLinks) {
        if (link.paramId == parameterID) {
            for (auto& adaptableParam: link.adaptableParameters) {
                adaptableParam.paramSetFunction(adaptableParam.var, *tree.getRawParameterValue(parameterID));
            }
        }
    }
```

### Editors / UI
Baseclass editor. In pluginEdittor everything comes together.
Editors and subeditors. example with modulationcomponent

Example with modulationcomponent
```C++
ModulationComponent::ModulationComponent(TransitionFxAudioProcessor& p, std::vector<string>& sliderIds) : Editor(p)
{
    createSliders(sliders, attachments, sliderIds, Slider::SliderStyle::LinearVertical, Slider::NoTextBox);
}

ModulationComponent::~ModulationComponent()
{
    deleteSliders(sliders, attachments);
}

void ModulationComponent::paint (juce::Graphics& g)
{
}

void ModulationComponent::resized()
{
    // draw the sliders
}
```
- picture

### Set time
Different types of time setting in frames seoncs and beats, to link well and precisily to picture

- picture

### Envelopes
Envelopes exist of statemachine. Value that needs to be added per sample is calculated. Linear steps are used with smooth option.

- code example

### Voice types

## Improvements
As this project is a refactor for a month long part-time codejam, a lot is to be added or improved. However, the project has been made with simplicity in mind and the goal was not to make an extensive synthesiser. More voices, effects, modulation and controll of the output could be added in the future.