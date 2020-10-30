# RFX WIP
 
RFX is a synthesiser instrument for designing transitional moving effects such as Whooshes, Risers and Stingers. I find there to be a lack of a intuitive synthesisers optimalised for creating these effects, which is why I started developing Transition FX. The user should be able to create the entire sound from within the plugin, without external effects or automation.

Development RFX is currently still in progress. MVP is set to be reached before the end of November. As this date comes closer, documentation will be updated.

RFX is written in C++ using the JUCE framework and [Maximilian DSP](https://github.com/micknoise/Maximilian) library. It is a refactor of the [TransitionFX ALPHA](https://github.com/StijndeK/TransitionFX-ALPHA), made for [Code With Friends Fall 2020](https://codewithfriends.io/events/cwf-fall-2020/).


## Design
Emphesis has been put on not overwelming the user with to many possibilities. It should be easy to make an impressive sounding riser quickly without any form of manual. Voices containing preset synthesis can be added or removed and given a type and effects can be loaded in and edited. Most control is provided in the modulation. 

Some of the most important elements of Risers  are:
- **A LOT of modulation**: the largest part of the plugin is a modulation editor
- **Length**: the attack and release length can be individually edited based on milliseconds, beats or frames (usefull when working with film)
- **Linking to context**: whether RiserFx is used for a visual medium or within a music track, it is important to be able to link the audio very precisly. *Beat Linking* allows the user to set the impact point, to then be able to edit attack and release, instead of having to move the midi everytime they want to change attack or release length

The design has been based of existing (mostly sample based) plugins such as: [GRAVITY](https://heavyocity.com/product/gravity/), [Whoosh](https://tonsturm.com/software/whoosh/) and [Rise & Hit](https://www.native-instruments.com/en/products/komplete/cinematic/rise-hit/). Air Music's; [The Riser](https://www.airmusictech.com/product/the-riser), was the only synthesis based plugin that I could find and provided a lot of insight in how to create heavy impact with limited input.

## Development

Made as dynamically as possible, to easily be able to add and change elements. However, because of some limitations with the JUCE framework as well as wanting to keep it simple for a montlong codejam the amount of voices are hardcoded. 

## Improvements
As this project is a refactor for a month long part-time codejam, a lot is to be added or improved. However, the project has been made with simplicity in mind and the goal was not to make an extensive synthesiser. More voices, effects, modulation and controll of the output could be added in the future.