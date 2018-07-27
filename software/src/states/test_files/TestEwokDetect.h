#include <Arduino.h>

#include "../State.h"
#include "../Pins.h"

class S_TestEwokDetect: public State {
    void onStart() {
        Serial.begin( 9600 );
        pinMode( R_CLAW_DETECT, INPUT_PULLUP );
    }
    
    void onLoop()  { 
        static uint64_t count = 0;
        if( count % 100 == 0 ) {
            Serial.println( analogRead( R_CLAW_DETECT ) ); 
        }
        count++;
    }
};
