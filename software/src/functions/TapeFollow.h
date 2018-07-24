#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "../functions/Motors.h"

#define KP_TAPE ((float) 2.5)
#define KD_TAPE ((float) 0.7)
#define KI_TAPE ((float) 0)

#define INTEGRAL_CUTOFF 150

#define SETPOINT 0
#define GAIN 1

#define R_MAX_SPEED 255
#define L_MAX_SPEED 255

#define TIME_DELAY 30

class TapeFollower {  
    public: 
        uint64_t lastWriteTime = 0;
    
        int16_t error = 0;
        int16_t errorDerivative = 0;
        int32_t errorIntegral = 0; 
        
        void poll( int speed ) {
            if( millis() - lastWriteTime > TIME_DELAY ) {
                int16_t farLeft    = analogRead( TF_FAR_LEFT );
                int16_t closeLeft  = analogRead( TF_CLOSE_LEFT );
                int16_t closeRight = analogRead( TF_CLOSE_RIGHT );
                int16_t farRight   = analogRead( TF_FAR_RIGHT );

                int16_t newError = ( farLeft + closeLeft - closeRight - farRight ) - SETPOINT;
                
                errorDerivative = newError - error;
                error = newError;

                int32_t motorCorrection = KP_TAPE * error + KD_TAPE * errorDerivative;
                
                if ( abs( error ) < INTEGRAL_CUTOFF ) {
                    errorIntegral += error;
                    motorCorrection += KI_TAPE * errorIntegral;
                }
                
                motorCorrection *= GAIN;

                uint8_t rightMotorSpeed = constrain( speed + motorCorrection, 0, R_MAX_SPEED );
                uint8_t leftMotorSpeed  = constrain( speed - motorCorrection, 0, L_MAX_SPEED );
                
                Motors::run( rightMotorSpeed, leftMotorSpeed );

                lastWriteTime = millis();
            }
        }
};
