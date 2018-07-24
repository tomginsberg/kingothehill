#pragma once

#include <Arduino.h>
#include "../Pins.h"

namespace Motors {
    void run( int rs, int ls ) {
        if ( ls > 0 ) {
            digitalWrite( L_MOTOR_B, 0 );
            delay( 5 );
            analogWrite( L_MOTOR_F, ls );
        } else {
            digitalWrite( L_MOTOR_F, 0 );
            delay( 5 );
            analogWrite( L_MOTOR_B, -ls );
        }
        
        if ( rs > 0 ){
            digitalWrite( R_MOTOR_B, 0 );
            delay( 5 );
            analogWrite( R_MOTOR_F, rs );
        } else {
            digitalWrite( R_MOTOR_F, 0 );
            delay( 5 );
            analogWrite( R_MOTOR_B, -rs );
        }
    }

    void stop() {
        digitalWrite( L_MOTOR_F, LOW );
        digitalWrite( R_MOTOR_F, LOW );
        digitalWrite( L_MOTOR_B, LOW );
        digitalWrite( R_MOTOR_B, LOW );        
    }
};
