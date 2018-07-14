#pragma once

#include <Arduino.h>

// The sum of these values must be less than 128
#define KP_TAPE 79
#define KD_TAPE 47
#define KI_TAPE 1

#if( KP_TAPE + KD_TAPE + KI_TAPE > 128 )
    #error "PID gains are too high, data structures may overflow!"
#endif

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
        int16_t errorDifferential = KD_TAPE * ( ( rawError >> 1 ) - ( prevErr >> 1 ) );
        int16_t errorIntegral     = KI_TAPE * ( ( errorSum + rawError ) >> 8 );

        int8_t motorCorrection;

        if( abs( rawError ) < INTEGRAL_CUTOFF ) {
            errorSum += rawError;
            motorCorrection = ( errorProportional + errorDifferential + errorIntegral ) >> 8;
        } else {
            motorCorrection = ( errorProportional + errorDifferential ) >> 8;
        }

        if( motorCorrection <= 0 ) {
            analogWrite( RIGHT_MOTOR_F, speed );  // Right Motor
            analogWrite(  LEFT_MOTOR_F, speed + constrain( motorCorrection, -255, 0 ) ); // Left Motor
        } else {
            analogWrite( RIGHT_MOTOR_F, speed - constrain( motorCorrection, 0,  255 ) ); // Right Motor
            analogWrite(  LEFT_MOTOR_F, speed ); // Left Motor
        }

        prevErr = rawError;
    }
}