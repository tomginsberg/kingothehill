#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"

#define WAIT_TIME 8200

class S_ClimbingBridge: public State {
    EdgeFollower ef;
    uint64_t startTime = millis();

    void onStart() {
        startTime = millis();
    }

    void onLoop() { 
        ef.poll( 120 );
    }

    bool transitionCondition() {
        // <tt>SeekingChewbacca<tt>
        return millis() - startTime > WAIT_TIME; 
    }
};
