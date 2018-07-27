#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"

class S_AcquireSecondEwok: public State {
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_R_CLAW );
        delay( 500 );
        Serial.write( CLOSE_R_CLAW );
        delay( 1000 );
        Serial.write( LIFT_R_CLAW );
        delay( 1500 );
        Serial.write( OPEN_R_CLAW );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( DETACH_R_CLAW );
        Serial.flush();
        Serial.end();
    }


    bool transitionCondition() {
        // <tt>IRSensing<tt>
        return true;
    }
};
