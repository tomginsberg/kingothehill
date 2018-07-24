#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
class S_StopAllFunctions: public State {
    void onStart() { 
        Motors::stop();
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>Null<tt> 
        return false;
    }
}
