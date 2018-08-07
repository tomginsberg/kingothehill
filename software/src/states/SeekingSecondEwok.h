#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;
    uint64_t startTime;
    bool a = true;

    void onStart() {
        tf.kpTape = 0.28;
        startTime = millis();
    }
    

    void onLoop() { 
        tf.poll( 90 );

        if(a and (millis()-startTime)>1000){
            tf.kdTape = 0.2;
            tf.MAX_SPEED=140;
            a=false;
        }
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_IN );
    }
};
