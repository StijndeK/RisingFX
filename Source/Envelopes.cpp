/*
  ==============================================================================

    Envelopes.cpp
    Created: 31 Oct 2018 1:40:53pm
    Author:  Stijn de Koning

  ==============================================================================
*/

#include "Envelopes.h"

//==============================================================================
double Envelopes::arLin(double input, int trigger)
{
    switch(currentEnvState) {
        case ATTACK:
            amplitude+=(1*attack);
            if (amplitude>=1) {
                amplitude=1;
                currentEnvState = HOLD;
            }
            break;
        case HOLD:
            amplitude = 1;
            if (trigger!=1) {
                currentEnvState = RELEASE;
            }
            break;
        case RELEASE:
            amplitude-=(1*release);
            if (amplitude<=0) {
                amplitude = 0;
                currentEnvState = STOP;
            }
            break;
        case STOP:
            amplitude = 0.0;
            if (trigger == 1) {
                currentEnvState = ATTACK;
            }
            break;
    }
    
    output = input * amplitude;
    return output;
}

//==============================================================================
double Envelopes::arExp(double input, int trigger)
{
    switch(currentEnvState) {
        case ATTACK:
            amplitude *= attack;
            if (amplitude >= 1) {
                amplitude = 1;
                currentEnvState = HOLD;
            }
            break;
        case HOLD:
            amplitude = 1;
            if (trigger !=1 ) {
                currentEnvState = RELEASE;
            }
            break;
        case RELEASE:
            amplitude *= (2 - release); // releasevalue is calculated as attackvalue in setADSRValue, to convert to release subtract the value of 2
            if (amplitude <= amplitudeStartValue) {
                amplitude = 0;
                currentEnvState = STOP;
            }
            break;
        case STOP:
            amplitude = 0.0;
            if (trigger == 1) {
                amplitude = amplitudeStartValue;
                currentEnvState = ATTACK;
            }
            break;
    }

    output = input * amplitude;
    return output;
}

//==============================================================================
double Envelopes::arLinSteps(double input, int trigger)
{
    switch(currentEnvState) {
        case ATTACK:
            amplitude += (1 * attacksAndReleases[currentStep]);
            
            if (amplitude >= steps[currentStep]) { // check if step needs to move forward
                amplitude = steps[currentStep];
                currentStep++;
                if (amplitude >= 1) { // check if this was the last step
                    currentEnvState = HOLD;
                }
            }
            break;
        case HOLD:
            amplitude = 1;
            if (trigger != 1) {
                currentEnvState = RELEASE;
            }
            break;
        case RELEASE:
            amplitude -= (1 * attacksAndReleases[currentStep]);
            
            if (amplitude <= steps[currentStep]) { // check if step needs to move forward
                amplitude = steps[currentStep];
                currentStep++;
                if (amplitude <= 0) { // check if this was the last step
                    currentEnvState = STOP;
                }
            }
            break;
        case STOP:
            amplitude = 0.0;
            if (trigger == 1) {
                currentEnvState = ATTACK;
                currentStep = 0;
            }
            break;
    }
        
    output = input * amplitude;
    return output;
}
