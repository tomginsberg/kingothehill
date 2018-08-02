#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_LoweringBasket: public State {
    void onStart() { 
        Motors::run( 110 );
        delay( 1000 );
        Serial.write( LOWER_BASKET );
        delay( 2000 );
        Motors::run( -110 );
        delay( 2000 );
    }

    void onEnd() {
         Motors::stop(); 
    }

    bool transitionCondition() {
        // <tt>StopAllFunctions<tt> 
        return true;
    }
};
