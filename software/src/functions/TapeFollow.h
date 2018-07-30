#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "Motors.h"

// #define KP_TAPE ((float) 1.5)
// #define KD_TAPE ((float) 0.6)
// #define KI_TAPE ((float) 0.01)
#define KP_TAPE ((float) 0.07)
#define KD_TAPE ((float) 0)
#define KI_TAPE ((float) 0)

#define SETPOINT 100
#define GAIN 1

#define MAX_SPEED 255

#define TIME_DELAY 5

#define DMAX 200
#define EMAX 200
#define IMAX 200

#define DEADBAND 205

class TapeFollower {  
    void scan( int dir ) {
        if( dir < 0 ) {
            Motors::run( 95, 15 );
        } else if( dir > 0 ) {
            Motors::run( 15, 95 );
        }
    }

    public: 
        bool scanning = false;
        uint64_t lastWriteTime = 0;
        
        float error = 0;
        float errorDerivative = 0;
        float errorIntegral = 0; 
        
        const uint8_t white[4] = { 0, 0, 0, 0 };
        
        void poll( uint8_t speed ) {
            static uint8_t lastSpeed[2] = { speed, speed };
            
            if( millis() - lastWriteTime > TIME_DELAY ) {
                int16_t farLeft    = map( analogRead( TF_FAR_LEFT ), 80, 750, 60, 600 );
                int16_t closeLeft  = analogRead( TF_CLOSE_LEFT );
                int16_t closeRight = analogRead( TF_CLOSE_RIGHT );
                int16_t farRight   = map( analogRead( TF_FAR_RIGHT ), 120, 400, 60, 600 );

                float newError = ( farLeft + closeLeft - closeRight - farRight ) - SETPOINT;
                if( farLeft < white[0] && closeLeft < white[1] && closeRight < white[2] && farRight < white[3] ) {
                    scan( errorIntegral );
                    scanning = true; 
                } else {
                    errorDerivative = newError - error;
                    error = newError;

                    int32_t motorCorrection = GAIN * (
                        constrain( KP_TAPE * error, -EMAX, EMAX ) + 
                        constrain( KD_TAPE * errorDerivative, -DMAX, DMAX ) +
                        constrain( KI_TAPE * errorIntegral, -IMAX, IMAX ) );
                    
                    uint8_t rightMotorSpeed = constrain( constrain( speed + motorCorrection, 20, MAX_SPEED ), lastSpeed[0] - DEADBAND, lastSpeed[0] + DEADBAND );
                    uint8_t leftMotorSpeed  = constrain( constrain( speed - motorCorrection, 20, MAX_SPEED ), lastSpeed[1] - DEADBAND, lastSpeed[1] + DEADBAND );
                    
                    lastSpeed[0] = rightMotorSpeed;
                    lastSpeed[1] = leftMotorSpeed;
                    
                    Motors::run( rightMotorSpeed, leftMotorSpeed );
                }

                lastWriteTime = millis();
            }
        }
};
