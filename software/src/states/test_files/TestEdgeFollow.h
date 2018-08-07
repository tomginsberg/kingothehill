#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"

class S_TestEdgeFollow: public State {
    EdgeFollower ef;
    bool stopped = false;

    void onStart() {
        Serial.begin( 9600 );
    }

    void onLoop() { 
        if( !stopped ) {
            ef.poll( 120 );
            uint16_t reading = analogRead( TF_EDGE_RIGHT );
            Serial.println( reading );
            if( reading < 240 ) {
                Motors::hardStop();
                stopped = true;
            }
        }
    }
};
