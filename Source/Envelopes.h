/*
  ==============================================================================

    Envelopes.h
    Created: 31 Oct 2018 1:40:53pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class Envelopes {
    
public:
    // arlin envelope states
    enum ArLinState {ATTACK, HOLD, RELEASE, STOP};
    
    // initial state
    ArLinState currentEnvState = STOP;
        
    // envelopes
    double arLin(double input, int trigger);
    double arExp(double input, int trigger);
    double arLinSteps(double input, int trigger);

    // Delay
    double delay(double input, int trigger);    // sends a delayed trigger
    double delayInput;

    float attack = 0;
    float release = 0;
    
    std::vector<float> steps; // by changing the height of the step change envelope shape
    std::vector<float> attacksAndReleases; // vector because in the future the user shoulsd be able to also edit env points horizontally, instead of it being the same value for every step
    int currentStep = 0;
    
    // samplerate
    double samplerate = 48000.0;
    double setSampleRate (double rate)
    {
        if (rate == 0){
            return 44100.0;
        }
        else {
            return rate;
        }
    }
    
    // other
    double output;
    double amplitude = 0.001;
    double amplitudeExp, amplitudeLin;
    double amplitudeStartValue = 0.001;     // define the startvalue for the exponential curve
};
