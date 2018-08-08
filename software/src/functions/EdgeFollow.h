#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "Motors.h"
#include "../GlobalVariables.h"

#define KP_EDGE ((float) 0.6)
#define KD_EDGE ((float) 0.7)

#define MAX_SPEED_EDGE 255

class EdgeFollower {
    int16_t error = 0;
    int16_t errorDerivative = 0;
    
    public:
        uint8_t lastLSpeed = 0;
        uint8_t lastRSpeed = 0;
        
        void poll( int speed ) {
            int16_t EDGE_SETPOINT = RIGHT_EDGE_BASELINE + 190;

            int16_t rawVal = analogRead( TF_EDGE_RIGHT );
            int16_t newError = rawVal - EDGE_SETPOINT;

            errorDerivative = newError - error;
            error = newError;

            int32_t motorCorrection = KP_EDGE * error + KD_EDGE * errorDerivative;

            uint8_t rightMotorSpeed = constrain( speed + motorCorrection, 0, MAX_SPEED_EDGE );
            uint8_t leftMotorSpeed = constrain( speed - motorCorrection, 0, MAX_SPEED_EDGE );

            lastLSpeed = leftMotorSpeed;
            lastRSpeed = rightMotorSpeed;

            Motors::run( rightMotorSpeed, leftMotorSpeed );
        }
};