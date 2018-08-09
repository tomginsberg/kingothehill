#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"
#include "../functions/Motors.h"

class S_AcquireThirdEwok: public State {
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( INIT_L_CLAW );
        Serial.write( CLOSE_L_CLAW );
        delay( 1200 );
        Motors::run(100);
        delay(300);
        Motors::stop();
        Serial.write( LIFT_L_CLAW );
        delay( 1700 );
        Serial.write( OPEN_L_CLAW );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }


    bool transitionCondition() {
        // <tt>Recalibrating<tt>
        return true;
    }
};
