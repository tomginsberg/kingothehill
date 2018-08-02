#pragma once

#include <Arduino.h>
#include "../Pins.h"

#define CLOCKWISE 1
#define C_CLOCKWISE 0

#define FORWARDS 1
#define BACKWARDS 0

namespace Motors {
    void run( int16_t rightSpeed, int16_t leftSpeed ) {
        static uint8_t lastLeftDir = 0;
        static uint8_t lastRightDir = 0;
        
        if ( leftSpeed > 0 ) {
            digitalWrite( L_MOTOR_B, 0 );
            delayMicroseconds( lastLeftDir == FORWARDS ? 0 : 50 );
            analogWrite( L_MOTOR_F, leftSpeed );
            lastLeftDir = FORWARDS;
        } else {
            digitalWrite( L_MOTOR_F, 0 );
            delayMicroseconds( lastLeftDir == BACKWARDS ? 0 : 50 );
            analogWrite( L_MOTOR_B, -leftSpeed );
            lastLeftDir = BACKWARDS;
        }
        
        if ( rightSpeed > 0 ) {
            digitalWrite( R_MOTOR_B, 0 );
            delayMicroseconds( lastRightDir == FORWARDS ? 0 : 50 );
            analogWrite( R_MOTOR_F, rightSpeed );
            lastRightDir = FORWARDS;
        } else {
            digitalWrite( R_MOTOR_F, 0 );
            delayMicroseconds( lastRightDir == BACKWARDS ? 0 : 50 );
            analogWrite( R_MOTOR_B, -rightSpeed );
            lastRightDir = BACKWARDS;
        }
    }

    void run( int16_t speed ) {
        run( speed, speed );
    }

    void stop() {
        digitalWrite( L_MOTOR_F, LOW );
        digitalWrite( R_MOTOR_F, LOW );
        digitalWrite( L_MOTOR_B, LOW );
        digitalWrite( R_MOTOR_B, LOW );        
    }

    void hardStop(){
        run( -255 );
        delay( 15 );
        stop();
    }

    void pivot( int16_t speed, uint8_t direction ) {
        if( direction ) {
            run( -speed, speed );
        } else {
            run( speed, -speed );
        }
    }
};
