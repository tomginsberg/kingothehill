#include <Arduino.h>

#include "../State.h"
#include "../Pins.h"
#include "../SerialIDs.h"

class S_RaisingBasket: public State {    
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( RAISE_BASKET );
    }

    void onEnd() {
        Serial.end();
    }
};