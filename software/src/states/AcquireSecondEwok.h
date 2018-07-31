#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"

class S_AcquireSecondEwok: public State {
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( INIT_R_CLAW );
        Serial.write( CLOSE_R_CLAW );
        Motors::hardStop();
        delay( 1000 );
        Serial.write( LIFT_R_CLAW );
        delay( 1500 );
        Serial.write( OPEN_R_CLAW );
        delay( 200 );
    }

    void onEnd() {
        Serial.write( DETACH_R_CLAW );
        Serial.write( LIFT_L_CLAW );
        delay( 400 );
        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }


    bool transitionCondition() {
        // <tt>IRSensing<tt>
        return true;
    }
};
