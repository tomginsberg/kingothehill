#include <Arduino.h>

#include "../State.h"
#include "../functions/Platform.h"

class S_TestGapCrossing3: public State {
    FirstPlatform platform;

    void onStart() {
        Serial.begin( 9600 );
        platform.release();
        delay( 30 );  // Could make this non-blocking?
        platform.drop();
    }

    bool transitionCondition() {
        // <tt>TestGapCrossing4<tt>
        return true;
    } 
};
