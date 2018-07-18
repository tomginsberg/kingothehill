#pragma once

#include <Arduino.h>

#include "../Pins.h"

#define INTEGRAL_CUTOFF 150  // This number should be less that 255 (the maximum allowed error value)

class TapeFollower {
    int8_t kp = 79;  // These are just some reasonable starting values
    int8_t kd = 47;
    int8_t ki = 1;

    int8_t speed = 255;
    
    public:
        void setConstants( int8_t _kp, int8_t _kd, int8_t _ki ) {
            if( kp + kd + ki <= 128 ) {
                kp = _kp;
                kd = _kd;
                ki = _ki;
            }
        } 

        void setSpeed( int8_t _speed ) {
            if( abs( _speed ) <= 255 ) {
                speed = _speed;
            }
        }
        
        void poll() {
            static int8_t prevErr = 0;
            static int16_t errorSum = 0;

            int16_t farLeft = analogRead( 0 );
            int16_t closeLeft = analogRead( 1 );
            int16_t closeRight = analogRead( 2 );
            int16_t farRight = analogRead( 3 );

            int16_t rawError = ( farLeft + closeLeft - closeRight - farRight ) >> 3;  // A number between -255 & 255

            int16_t errorProportional = kp * rawError;
            int16_t errorDifferential = kd * ( ( rawError >> 1 ) - ( prevErr >> 1 ) );
            int16_t errorIntegral     = ki * ( ( errorSum + rawError ) >> 8 );

            int8_t motorCorrection;

            if( abs( rawError ) < INTEGRAL_CUTOFF ) {
                errorSum += rawError;
                motorCorrection = ( errorProportional + errorDifferential + errorIntegral ) >> 8;
            } else {
                motorCorrection = ( errorProportional + errorDifferential ) >> 8;
            }

            if( motorCorrection <= 0 ) {
                analogWrite( R_MOTOR_F, speed );  // Right Motor
                analogWrite( L_MOTOR_F, speed + constrain( motorCorrection, -255, 0 ) ); // Left Motor
            } else {
                analogWrite( R_MOTOR_F, speed - constrain( motorCorrection, 0,  255 ) ); // Right Motor
                analogWrite( L_MOTOR_F, speed ); // Left Motor
            }

            prevErr = rawError;
        }
};
