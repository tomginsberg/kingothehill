#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../Pins.h"

#define MAX_SEEKING_TIME 2000
#define MILLIS_FREQ 50  // Number of frames

class S_SeekingFirstEwok: public State {
    TapeFollower tf;

    uint64_t startTime = millis();
    uint64_t currentTime = 0;

    void onLoop() { 
        static uint16_t count = 0; 
        tf.poll( 120 ); 

        if( count % MILLIS_FREQ == 0 ) {
            currentTime = millis();
        }     

        count++;  
    }

    bool transitionCondition() {
        // <tt>AcquireFirstEwok<tt> 
        return digitalRead( R_CLAW_COMM_OUT );
    }

    bool errorCondition() {
        // <tt>StopAllFunctions<tt>
        return currentTime - startTime > MAX_SEEKING_TIME;
    }
};
