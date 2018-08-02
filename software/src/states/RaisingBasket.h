#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_RaisingBasket: public State {
    void onStart() { 
        Motors::run( -100 );
        Serial.begin( 9600 );
        Serial.write( RAISE_BASKET );
<<<<<<< HEAD
        delay( 400 );
        Motors::stop();
        delay( 11500 );
=======
        delay( 700 );
        Motors::stop();
        delay( 9500 );
>>>>>>> 7bc926b5364ccb42efce1d444fd1293909c06cf0
    }

    bool transitionCondition() {
        // <tt>LoweringBasket<tt> 
        return true;
    }
};
