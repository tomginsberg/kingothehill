#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"

class S_SeekingFourthEwok: public State {
    void onLoop() { 
        Motors::run( -10, 130 );
    }

    void onEnd() { 
        Motors::stop(); 
    }

    bool transitionCondition() {
        // <tt>AcquireFourthEwok<tt> 
        return digitalRead( L_CLAW_COMM_IN );
    }
};
