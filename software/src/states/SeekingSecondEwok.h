#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;

    void onStart() {
        tf.kdTape = 0.09;
    }
    void onLoop() { 
        tf.poll( 105 ); 
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_IN );
    }
};
