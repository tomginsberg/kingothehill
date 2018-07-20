#pragma once

#include <Arduino.h>

#include "../Pins.h"
#include "../functions/Motors.h"

// The sum of these values must be less than 128
#define KP_TAPE 2.8
#define KD_TAPE 0
#define KI_TAPE 0

#define INTEGRAL_CUTOFF 150  // This number should be less that 255 (the maximum allowed error value)

#define SETPOINT 0
#define GAIN 1

#define R_BASE_SPEED 90
#define L_BASE_SPEED 90

#define R_MAX_SPEED 220
#define L_MAX_SPEED 220

#define FORWARDS 1
#define BACKWARDS -1

#define WHITE 50

namespace TapeFollow {
     void scan( int dir ) {
        switch( dir ) {
            case FORWARDS: Motors::run( 115, 25 );
            case BACKWARDS: Motors::run( 25, 115 );
        }
    }  
    
     void poll() {
        static double lastError = 0;
        static double errorSum = 0;

        int s0 = analogRead( TF_FAR_LEFT );
        int s1 = analogRead( TF_CLOSE_LEFT );
        int s2 = analogRead( TF_CLOSE_RIGHT );
        int s3 = analogRead( TF_FAR_RIGHT );
      
        double error = ( s0 + s1 - s2 - s3 ) - SETPOINT;
      
        if( s0 < WHITE && s1 < WHITE ) {
            scan( FORWARDS );
            errorSum = 0;
        } else if( s2 < WHITE && s3 < WHITE ) {
            scan( BACKWARDS );
            errorSum = 0;
        } else {
            int motorCorrection = KP_TAPE * error + KD_TAPE * (error - lastError);
            
            if ( abs( error ) < INTEGRAL_CUTOFF ) {
                errorSum += error;
                motorCorrection += KI_TAPE * errorSum;
            }
            
            motorCorrection *= GAIN;
            lastError = error;

            int rightMotorSpeed = constrain( R_BASE_SPEED + motorCorrection, 0, R_MAX_SPEED );
            int leftMotorSpeed  = constrain( L_BASE_SPEED - motorCorrection, 0, L_MAX_SPEED );
            
            Motors::run( rightMotorSpeed, leftMotorSpeed );

            Serial.println( error );
        }
    }


}
