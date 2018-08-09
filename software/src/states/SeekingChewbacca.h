#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"

class S_SeekingChewbacca: public State {
    void onEnd() {
        Motors::stop();
    }

    bool transitionCondition() {
        // <tt>AcquireChewbacca<tt>
        return digitalRead( L_CLAW_COMM_IN );
    }

    bool errorCondition() {
        // <tt>BackingUp<tt>
        return analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR && analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR;
    }
};
