#include <Arduino.h>

#include "../State.h"
#include "../Pins.h"
#include "../GlobalVariables.h"
#include "../SerialIDs.h"
#include "../functions/TapeFollow.h"

class S_Calibrating: public State {
    void onStart() { 
        Serial.begin( 9600 );

        // Do not delete!!
        Serial.write( INIT_R_CLAW );
        Serial.write( OPEN_R_CLAW );
        Serial.write( LIFT_R_CLAW );
        Serial.write( LOWER_R_CLAW );
        delay( 400 );
        Serial.write( DETACH_R_CLAW );

        Serial.write( INIT_PLATFORM_1 );
        Serial.write( DETACH_PLATFORM_1 );

        SETPOINT = ( TapeFollower::readFarLeft()  + TapeFollower::readCloseLeft()  ) -
                   ( TapeFollower::readFarRight() + TapeFollower::readCloseRight() );
        RIGHT_EDGE_BASELINE = analogRead(TF_EDGE_RIGHT);
        LEFT_EDGE_BASELINE = analogRead(TF_EDGE_LEFT);  
    }

    void onEnd() {
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>Recalibrating<tt> 
        return true;
    }

};
