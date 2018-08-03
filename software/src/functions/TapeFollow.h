#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "Motors.h"

#define GAIN 1

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
        float kpTape = 0.16;
        float kdTape = 0.0005;
        float kiTape = 0.001;

        uint16_t MAX_SPEED = 255;

        bool scanning = false;
        uint64_t lastWriteTime = 0;
        
        float error = 0;
        float errorDerivative = 0;
        float errorIntegral = 0; 
        
        const uint8_t white[4] = { 0, 0, 0, 0 };

        void poll( uint8_t speed ) {
            static uint8_t lastSpeed[2] = { speed, speed };
            
            if( millis() - lastWriteTime > TIME_DELAY ) {
                int16_t farLeft    = readFarLeft();
                int16_t closeLeft  = readCloseLeft();
                int16_t closeRight = readCloseRight();
                int16_t farRight   = readFarRight();

                float newError = ( farLeft + closeLeft - closeRight - farRight ) - 20;
                if( farLeft < white[0] && closeLeft < white[1] && closeRight < white[2] && farRight < white[3] ) {
                    scan( errorIntegral );
                    scanning = true; 
                } else {
                    errorDerivative = newError - error;
                    error = newError;

                    int32_t motorCorrection = GAIN * (
                        constrain( kpTape * error, -EMAX, EMAX ) + 
                        constrain( kdTape * errorDerivative, -DMAX, DMAX ) +
                        constrain( kiTape * errorIntegral, -IMAX, IMAX ) );
                    
                    uint8_t rightMotorSpeed = constrain( constrain( speed + motorCorrection, 20, MAX_SPEED ), lastSpeed[0] - DEADBAND, lastSpeed[0] + DEADBAND );
                    uint8_t leftMotorSpeed  = constrain( constrain( speed - motorCorrection, 20, MAX_SPEED ), lastSpeed[1] - DEADBAND, lastSpeed[1] + DEADBAND );
                    
                    lastSpeed[0] = rightMotorSpeed;
                    lastSpeed[1] = leftMotorSpeed;
                    
                    Motors::run( rightMotorSpeed, leftMotorSpeed );
                }

                lastWriteTime = millis();
            }
        }

        static uint16_t readFarLeft() {
            return map( analogRead( TF_FAR_LEFT ), 80, 750, 50, 500 );
        } 

        static uint16_t readCloseLeft() {
            return analogRead( TF_CLOSE_LEFT );
        }

        static uint16_t readCloseRight() {
            return analogRead( TF_CLOSE_RIGHT );
        }

        static uint16_t readFarRight() {
            return map( analogRead( TF_FAR_RIGHT ), 100, 400, 50, 500 );
        }
};
