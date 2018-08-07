#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_RaisingBasket: public State {
    void onStart() { 
        Motors::run( -100 );
        Serial.begin( 9600 );
        Serial.write( RAISE_BASKET_MASTER );
        delay( 400 );
        Motors::stop();
        delay( 9200 );
    }

    bool transitionCondition() {
        // <tt>LoweringBasket<tt> 
        return true;
    }
};
