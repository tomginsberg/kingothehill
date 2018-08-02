#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"

class S_SeekingChewbacca: public State {
    void onStart() { 
        Motors::run( 110, 150 );
    }

    void onEnd() {
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireChewbacca<tt> 
        return digitalRead( L_CLAW_COMM_IN );
    }
};
