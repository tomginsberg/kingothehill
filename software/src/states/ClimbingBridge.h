#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"

#define WAIT_TIME 8000

class S_ClimbingBridge: public State {
    EdgeFollower ef;
    uint64_t startTime = millis();

    void onStart() {
        startTime = millis();
        Serial.begin( 9600 );
        Serial.write( RAISE_BASKET_A_BIT );
    }

    void onLoop() { 
        ef.poll( 120 );
    }

    bool transitionCondition() {
        // <tt>SeekingChewbacca<tt>
        return millis() - startTime > WAIT_TIME; 
    }
};
