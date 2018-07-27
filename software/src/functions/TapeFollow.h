#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "Motors.h"

// #define KP_TAPE ((float) 1.5)
// #define KD_TAPE ((float) 0.6)
// #define KI_TAPE ((float) 0.01)
#define KP_TAPE ((float) 2)
#define KD_TAPE ((float) 1.7)
#define KI_TAPE ((float) 0.01)

#define SETPOINT 0
#define GAIN 1

#define MAX_SPEED 230

#define TIME_DELAY 20

#define DMAX 20
#define EMAX 40
#define IMAX 50

#define DEADBAND 15

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
        
        int16_t error = 0;
        int16_t errorDerivative = 0;
        int32_t errorIntegral = 0; 
        
        const uint8_t white[4] = { 0, 0, 0, 0 };
        
        void poll( uint8_t speed ) {
            static uint8_t lastSpeed[2] = { speed, speed };
            
            if( millis() - lastWriteTime > TIME_DELAY ) {
                int16_t farLeft    = analogRead( TF_FAR_LEFT );
                int16_t closeLeft  = analogRead( TF_CLOSE_LEFT );
                int16_t closeRight = analogRead( TF_CLOSE_RIGHT );
                int16_t farRight   = analogRead( TF_FAR_RIGHT );

                int16_t newError = ( farLeft + closeLeft - closeRight - farRight ) - SETPOINT;
                if( farLeft < white[0] && closeLeft < white[1] && closeRight < white[2] && farRight < white[3] ) {
                    scan( errorIntegral );
                    scanning = true; 
                } else {
                    if( scanning == true ) {
                        scanning = false;
                        errorIntegral = 0;
                    }
                    errorDerivative = newError - error;
                    error = newError;

                    int32_t motorCorrection = GAIN * (
                        constrain( KP_TAPE * error, -EMAX, EMAX ) + 
                        constrain( KD_TAPE * errorDerivative, -DMAX, DMAX ) +
                        constrain( KI_TAPE * errorIntegral, -IMAX, IMAX ) );

                    if( abs( error ) > 5 ) {
                        errorIntegral = 0;
                    }
                    
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
