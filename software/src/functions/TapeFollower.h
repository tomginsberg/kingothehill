#pragma once

#include <Arduino.h>

#include "../Pins.h"

#define INTEGRAL_CUTOFF 150  // This number should be less that 255 (the maximum allowed error value)

class TapeFollower {
    int8_t kp = 79;  // These are just some reasonable starting values
    int8_t kd = 47;
    int8_t ki = 1;

    int32_t speed = 0;
    
    int8_t running = false;

    public:
        void setConstants( int8_t _kp, int8_t _kd, int8_t _ki ) {
            if( kp + kd + ki < 128 ) {
                kp = _kp;
                kd = _kd;
                ki = _ki;
            }
        }

        void start() {
            running = true;
        } 

        void stop() {
            analogWrite( R_MOTOR_F, 0 );
            analogWrite( L_MOTOR_F, 0 );
            running = false;
        }

        void setSpeed( int16_t _speed ) {
            if( abs( _speed ) < 256 ) {
                speed = _speed;
            }
        }
        
        void poll() {
            if( running ) {
                static int16_t prevErr = 0;
                static int16_t errorSum = 0;

                int16_t farLeft = analogRead( TF_FAR_LEFT );
                int16_t closeLeft = analogRead( TF_CLOSE_LEFT );
                int16_t closeRight = analogRead( TF_CLOSE_RIGHT );
                int16_t farRight = analogRead( TF_FAR_RIGHT );

                int16_t rawError = ( farLeft + closeLeft - closeRight - farRight ) >> 3;  // A number between -255 & 255

                int16_t errorProportional = kp * rawError;
                int16_t errorDifferential = kd * ( ( rawError >> 1 ) - ( prevErr >> 1 ) );
                int16_t errorIntegral     = ki * ( ( errorSum + rawError ) >> 8 );

                int16_t motorCorrection;

                if( abs( rawError ) < INTEGRAL_CUTOFF ) {
                    errorSum += rawError;
                    motorCorrection = ( errorProportional + errorDifferential + errorIntegral ) >> 8;
                } else {
                    motorCorrection = ( errorProportional + errorDifferential ) >> 8;
                }

                int16_t l_speed, r_speed;

                if( motorCorrection <= 0 ) {
                    l_speed = speed * ( 255 + constrain( motorCorrection, -255, 0 ) ) / 255;
                    r_speed = speed;
                } else {
                    l_speed = speed;
                    r_speed = speed * ( 255 - constrain( motorCorrection, 0, 255 ) ) / 255;
                }

                analogWrite( R_MOTOR_F, r_speed );
                analogWrite( L_MOTOR_F, l_speed );

                prevErr = rawError;
            }
        }
};
