#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;

    void onLoop() { 
        tf.poll( 100 ); 
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_IN );
    }
};
