#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingSecondEwok: public State {
    TapeFollower tf;

    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_L_CLAW );
        Serial.write( LIFT_L_CLAW ); 
        Serial.write( CLOSE_L_CLAW);
        Motors::run(90,90);
        delay(1000);
    }

    void onLoop()  { 
        tf.poll( 70 ); 
    }

    void onEnd() {
        Motors::stop();

        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>AcquireSecondEwok<tt>
        return digitalRead( R_CLAW_COMM_OUT );
    }
};
