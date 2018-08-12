#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_RaisingBasket: public State {
    void onStart() { 
        Motors::run( -100,-105 );
        Serial.begin( 9600 );
        Serial.write( RAISE_BASKET_MASTER );
        delay( 450 );
        Motors::stop();
        delay( 6900 );
    }

    bool transitionCondition() {
        // <tt>LoweringBasket<tt> 
        return true;
    }
};
