#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../Pins.h"
#include "../functions/Motors.h"

class S_SeekingFirstEwok: public State {
    TapeFollower tf;

    void onLoop() { 
        tf.poll( 110 ); 
    }

    void onEnd() {
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireFirstEwok<tt> 
        return digitalRead( R_CLAW_COMM_OUT );
    }
};
