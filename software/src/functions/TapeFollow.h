#pragma once

#include <Arduino.h>

#include "../Pins.h"

// The sum of these values must be less than 128
#define KP_TAPE 128
#define KD_TAPE 0
#define KI_TAPE 0

#define INTEGRAL_CUTOFF 150  // This number should be less that 255 (the maximum allowed error value)

namespace TapeFollow {
    void poll( int32_t speed ) {
        static int16_t prevErr = 0;
        static int16_t errorSum = 0;

        int16_t farLeft = analogRead( TF_FAR_LEFT );
        int16_t closeLeft = analogRead( TF_CLOSE_LEFT );
        int16_t closeRight = analogRead( TF_CLOSE_RIGHT );
        int16_t farRight = analogRead( TF_FAR_RIGHT ); 

        Serial.println( closeLeft );

        int16_t rawError = ( farLeft + closeLeft - closeRight - farRight ) >> 3;  // A number between -255 & 255

        Serial.println( rawError );

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


        int16_t l_speed = 0, r_speed = 0;

        if( motorCorrection <= 0 ) {
            l_speed = speed * ( 255 + constrain( motorCorrection, -255, 0 ) ) / 255;
            r_speed = speed;
        } else {
            l_speed = speed;
            r_speed = speed * ( 255 - constrain( motorCorrection, 0, 255 ) ) / 255;
        }

        analogWrite( R_MOTOR_F, r_speed );
        digitalWrite( R_MOTOR_B, LOW );
        analogWrite( L_MOTOR_F, l_speed );
        digitalWrite( L_MOTOR_B, LOW );

        prevErr = rawError;
    }
}
