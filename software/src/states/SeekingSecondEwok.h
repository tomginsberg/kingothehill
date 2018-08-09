#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;
    uint64_t startTime;

    void onStart() {
        tf.kdTape = 0.25;
        //old 0.16
        tf.MAX_SPEED = 117;
    }
    

    void onLoop() { 
        tf.poll( 110 );
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_IN );
    }
};
