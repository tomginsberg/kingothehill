#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"

class S_SeekingChewbacca: public State {
    void onStart() {
        Motors::run( 130,140 );
    }
    
    void onEnd() {
        Motors::stop();
    }

    bool transitionCondition() {
        // <tt>AcquireChewbacca<tt> 
        return digitalRead( L_CLAW_COMM_IN );
    }
};
