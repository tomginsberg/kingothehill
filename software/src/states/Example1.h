#include "../State.h"
#include <Arduino.h>

class S_Example1: public State {
    // This states does nothing while it is active and transitions after 4 seconds

    public:
        // <tt>Example2</tt>
        bool transitionCondition() {
            static const uint64_t startTime = millis();  // This is only assigned on the first call to this function
            static const uint32_t waitingTime = 4000;
            return millis() - startTime > waitingTime;  
        }

};