#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"

class S_AcquireChewbacca: public State {
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_L_CLAW );
        Serial.write( CLOSE_L_CLAW );
        delay( 1000 );
        Serial.write( LIFT_L_CLAW );
        delay( 1500 );
        Serial.write( OPEN_L_CLAW );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( LOWER_L_CLAW );
        delay( 700 );
        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }


    bool transitionCondition() {
        // <tt>RaisingBasket<tt>
        return true;
    }
};
