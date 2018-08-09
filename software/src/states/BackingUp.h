#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_BackingUp: public State {
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( INIT_L_CLAW );
        Serial.write( CLOSE_L_CLAW );
        delay( 1200 );
        Serial.write( LIFT_L_CLAW );
        delay( 2000 );
        Serial.write( LEFT_CLAW_OPEN_WIDE );
        delay( 1200 );
        Serial.write( LOWER_L_CLAW );
        Motors::run( -110, -100 );   
        delay( 700 );     
    }

    bool transitionCondition() {
        // <tt>RaisingBasket<tt> 
        return true;
    }
};
