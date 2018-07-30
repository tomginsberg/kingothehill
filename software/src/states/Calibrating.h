#include <Arduino.h>

#include "../State.h"
#include "../Pins.h"
#include "../GlobalVariables.h"
#include "../SerialIDs.h"

class S_Calibrating: public State {
    void onStart() { 
        Serial.begin( 9600 );

        // Do not delete!!
        Serial.write( INIT_R_CLAW );
        Serial.write( OPEN_R_CLAW );
        Serial.write( LIFT_R_CLAW );
        delay( 400 );
        Serial.write( DETACH_R_CLAW );

        Serial.write( INIT_PLATFORMS );
        Serial.write( DETACH_PLATFORMS );

        LEFT_EDGE_BASELINE = analogRead( TF_EDGE_LEFT );
        RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
    }

    void onEnd() {
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>ClimbingBridge<tt> 
        return true;
    }

};