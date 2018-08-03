#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_LoweringBasket: public State {
    void onStart() { 
        Motors::run( 100, 110 );
        delay( 850 );
        Motors::stop();
        Serial.write( LOWER_BASKET );
        delay( 3000 );
        Motors::run( -110 );
        delay( 1800 );
    }

    void onEnd() {
         Motors::stop(); 
    }

    bool transitionCondition() {
        // <tt>StopAllFunctions<tt> 
        return true;
    }
};
