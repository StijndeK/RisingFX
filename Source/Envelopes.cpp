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
    
    output = input*amplitude;
    return output;
}


void Envelopes::setADSRValue(double lengthInMs, double &ADSRState, bool exp)
{
    if (exp) {
        // TODO: implement the exponential envelope in a way, that both attack and release can be calculated the same way
        if (ADSRState == attack) {
            ADSRState = pow((1.0/amplitudeStartValue), 1.0 / (samplerate * (lengthInMs / 1000.0)));
        }
        else {
            ADSRState = pow((amplitudeStartValue/1), 1.0/ (samplerate * (lengthInMs / 1000.0)));
        }
    }
    else {
        ADSRState = (1.0/samplerate) * (1.0 / (lengthInMs / 1000.0));
    }
}

