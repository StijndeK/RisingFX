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

// linear returns the value by which to add/subtract, exponential returns a value to multiply by
void Envelopes::setADSRValue(double lengthInMs, float &ADSRState, bool exp)
{
    if (exp) {
        ADSRState = pow((1.0 / amplitudeStartValue), 1.0 / (samplerate * (lengthInMs / 1000.0)));
    }
    else {
        ADSRState = (1.0 / samplerate) * (1.0 / (lengthInMs / 1000.0));
    }
}


