#include <Arduino.h>

#include "../State.h"
#include "../Pins.h"
#include "../SerialIDs.h"

class S_LoweringBasket: public State {    
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( LOWER_BASKET );
    }

    void onEnd() {
        Serial.end();
    }
};
