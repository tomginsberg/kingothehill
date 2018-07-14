#pragma once

#include <Arduino.h>

// These values must be between -64 & 64.
#define KP_TAPE 55
#define KD_TAPE 32
#define KI_TAPE 1

#define INTEGRAL_CUTOFF 150  // This number should be less that 255 (the maximum allowed error value)

#define RIGHT_MOTOR_F 5
#define  LEFT_MOTOR_F 6

namespace TapeFollow {
    void poll( int speed ) {
        static int8_t prevErr = 0;
        static int16_t errorSum = 0;

        int16_t farLeft = analogRead( 0 );
        int16_t closeLeft = analogRead( 1 );
        int16_t closeRight = analogRead( 2 );
        int16_t farRight = analogRead( 3 );

        int16_t rawError = ( farLeft + closeLeft - closeRight - farRight ) >> 3;  // A number between -255 & 255

        int16_t errorProportional = KP_TAPE * rawError;
        int16_t errorDifferencial = KD_TAPE * ( ( rawError >> 1 ) - ( prevErr >> 1 ) );
        int16_t errorIntegral     = KI_TAPE * ( ( errorSum + rawError ) >> 8 );

        int8_t motorCorrection = ( errorProportional + errorDifferencial ) >> 8;

        if( abs( rawError ) < INTEGRAL_CUTOFF ) {
            errorSum += rawError;
            motorCorrection += errorIntegral >> 8;
        }

        if( motorCorrection <= 0 ) {
            analogWrite( RIGHT_MOTOR_F, speed );  // Right Motor
            analogWrite(  LEFT_MOTOR_F, speed + constrain( motorCorrection, -255, 0 ) ); // Left Motor
        } else {
            analogWrite( RIGHT_MOTOR_F, speed - constrain( motorCorrection, 0,  255 ) ); // Right Motor
            analogWrite(  LEFT_MOTOR_F, speed ); // Left Motor
        }


    }
}