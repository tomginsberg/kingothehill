#include <Arduino.h>
#include "../Pins.h"

namespace Motors {
    void run( int rs, int ls ) {
        if ( ls > 0 ) {
            analogWrite( L_MOTOR_F, ls );
            digitalWrite( L_MOTOR_B, 0 );
        } else {
            analogWrite( L_MOTOR_B, -ls );
            digitalWrite( L_MOTOR_F, 0 );
        }
        
        if ( rs > 0 ){
            analogWrite( R_MOTOR_F, rs );
            digitalWrite( R_MOTOR_B, 0 );
        } else {
            analogWrite( R_MOTOR_B, -rs );
            digitalWrite( R_MOTOR_F, 0 );
        }
    }

    void stop() {
        digitalWrite( L_MOTOR_F, LOW );
        digitalWrite( R_MOTOR_F, LOW );
        digitalWrite( L_MOTOR_B, LOW );
        digitalWrite( R_MOTOR_B, LOW );        
    }
};