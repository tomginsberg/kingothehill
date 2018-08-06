#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"

class S_SeekingChewbacca: public State {
    void onEnd() {
        delay( 50 );
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireChewbacca<tt> 
        return digitalRead( L_CLAW_COMM_IN );
    }
};
