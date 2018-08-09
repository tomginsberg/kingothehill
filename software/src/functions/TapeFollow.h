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
    bool outsideSensorsDisabled = false;
   
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
        uint16_t minSpeed = 20;

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

                if( outsideSensorsDisabled ) {
                    farLeft = 0;
                    farRight = 0;
                }

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
                    
                    uint8_t rightMotorSpeed = constrain( constrain( speed + motorCorrection, minSpeed, MAX_SPEED ), lastSpeed[0] - DEADBAND, lastSpeed[0] + DEADBAND );
                    uint8_t leftMotorSpeed  = constrain( constrain( speed - motorCorrection, minSpeed, MAX_SPEED ), lastSpeed[1] - DEADBAND, lastSpeed[1] + DEADBAND );
                    
                    lastSpeed[0] = rightMotorSpeed;
                    lastSpeed[1] = leftMotorSpeed;
                    
                    Motors::run( rightMotorSpeed, leftMotorSpeed );
                }

                lastWriteTime = millis();
            }
        }

        static uint16_t readFarLeft() {
            return map( analogRead( TF_FAR_LEFT ), 75, 589, 50, 500 );
        } 

        static uint16_t readCloseLeft() {
            return map( analogRead( TF_CLOSE_LEFT ), 71, 426, 50, 500 );
        }

        static uint16_t readCloseRight() {
            return map( analogRead( TF_CLOSE_RIGHT ), 71, 456, 50, 500 );
        }

        static uint16_t readFarRight() {
            return map( analogRead( TF_FAR_RIGHT ), 115, 392, 50, 500 );
        }

        static bool onBlack( uint8_t sensorVal ) {
            switch( sensorVal ) {
                case TF_FAR_LEFT: 
                    {
                        return readFarLeft() > 330;
                        break;
                    }
                case TF_CLOSE_LEFT: 
                    {
                        return readCloseLeft() > 330;
                        break;
                    }
                case TF_CLOSE_RIGHT: 
                    {
                        return readCloseRight() > 330;
                        break;
                    }
                case TF_FAR_RIGHT: 
                    {
                        return readFarRight() > 330;
                        break;
                    }
            }
        }

        void disableOutsideSensors() {
            outsideSensorsDisabled = true;
        }
};
