#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../Pins.h"
#include "../functions/Motors.h"

class S_SeekingFirstEwok: public State {
    TapeFollower tf;
    void onStart(){
        LEFT_EDGE_BASELINE = analogRead( TF_EDGE_LEFT );
        RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
        Serial.begin(9600);
        delay( 400 );
        Serial.write( INIT_PLATFORMS );
        delay(300);
        Serial.write( DETACH_PLATFORMS );
        Serial.end();
    }
    void onLoop() { 
        tf.poll( 170 ); 
    }

    void onEnd() {
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireFirstEwok<tt> 
        return digitalRead( R_CLAW_COMM_OUT );
    }
};
