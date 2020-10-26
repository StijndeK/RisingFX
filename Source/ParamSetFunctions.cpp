/*
  ==============================================================================

    ParamSetFunctions.cpp
    Created: 18 Oct 2020 6:15:33pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "ParamSetFunctions.h"
#include "Parameters.h"
#include "PluginProcessor.h"

// TODO: env setters need a value for what the step per sample is. Solution could be to have the last value of the valuetochange be this value. However, this ofcourse isnt very optimal.
void setEnvSteps(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    float samplerate = 48000;
    for (auto& value: valueToChange) {
        *value = (1.0 / samplerate) * (1.0 / (inputValue / 1000.0));
    }
}

void getProcessor (TransitionFxAudioProcessor* p)
{
    std::cout << p->parameters.attackMs << std::endl;
}

//void setStepEnvSteps(std::vector<float*> valueToChange, std::vector<std::atomic<float>&> inputValue) // inputvalues are steps, last value is the length of the entire envelope. valuestochange are the add or subtract values per step
//{
//
//    // TODO: moet of inputvalue een vector maken. zou simpelweg kunnen door de range en stepvalue van elke slider aan te passen wanneer een slider aanpast zodat de slider altijd de change terug geeft. Anders heb je de inputvalue van de slider voor nodig om te kunnen zien hoeveel afstand er nodig is
//    // TODO: heb echter sowieso meer inputvalues nodig ook om samplerate en framerate te krijgen in deze functies
//    // TODO: inputvalue is altijd de slidervalue in dit systeem, dat beter zo laten. bij valuetochange andere dingen meegeven. maar wel heel duidelijk bij schrijven en schrijven waarom het verkeerd is. dan mag het. (opschrijven dat je eigenlijk wilt dat paramsetfunctions member functie is )
//    // TODO: mss dan gewoon toch paramsetfunctions member maken, anders moet je lelijk zo met de valuetochange dingen aanpassen. Je kan dat voor nu wel doen maar dan bijschrijven dat dat wel echt moet.
//
//    float samplerate = 48000;
//
//    // get difference from steps
//
//    // algorythm calculates the add/subtract value per sample by getting the time and amount of amplitude that needs to be reached in the amount of time
//
//    for (int i = 0; i < inputValue.size(); i++) {
//        float amountOfAmplitude = std::abs(inputValue[i] - inputValue[i - 1]); // difference
//        *value = (1.0 / samplerate) * (1.0 / (inputValue / 1000.0));
//    }
//}
//
//// TODO: get these values from input and link with paramsetfunction (will be difficult because you need 2 values.. so maybe just give them both in a vector again as the 'cheap' solution . 2de value is dat de attack. mbv de attack + steps kan ik het uitvinden (je wilt dan als 1 stepslider verandert gelijk alle meegeven, wss door een slider met meer knobs of anders gewoon door dezelfde listener aan allemaal te hangen))
//// TODO: get envelope from parameters instead of making new one
//env->steps = {0.1, 0.2, 0.3, 1, 0.1, 0.075, 0.05, 0};
//float amountOfTimeAttack = 4000;
//float amountOfTimeRelease = 8000;
//for (int i = 0; i < env->steps.size(); i++) {
//    float amountOfAmplitude = std::abs(env->steps[i] - env->steps[i - 1]); // difference
//    if (i < 4) {
//        env->attacksAndReleases.push_back((amountOfAmplitude / 48000) * (1.0 / ((amountOfTimeAttack / 4) / 1000.0)));
//    }
//    else {
//        env->attacksAndReleases.push_back((amountOfAmplitude / 48000) * (1.0 / ((amountOfTimeRelease / 4) / 1000.0)));
//    }
//}
//// TODO: maybe attacks and release should be seperate, as the attack and release sliders are seperate as well. or find a way how amountoftime can be in one vector as well (by creating a vector of attack and release times)

void setEnvStepsFrames(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    float framerate;
    for (auto& value: valueToChange) {
        *value = (1.0 / framerate) * (1.0 / (inputValue / 1000.0));
    }
}

void setGain(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    for (auto& value: valueToChange) {
        *value = pow(10, inputValue / 20);
    }
}

void setSimpleValue(std::vector<float*> valueToChange, std::atomic<float>& inputValue, TransitionFxAudioProcessor* p)
{
    for (auto& value: valueToChange) {
        *value = inputValue;
    }
}

