#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../Pins.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../SerialIDs.h"

class S_SeekingFirstEwok: public State {
    TapeFollower tf;
    uint64_t startTime = millis();
    void onStart(){
        LEFT_EDGE_BASELINE = analogRead( TF_EDGE_LEFT );
        RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
        Serial.begin(9600);
        delay( 400 );
        Serial.write( INIT_PLATFORM_1 );
        delay(305);
        Serial.write( DETACH_PLATFORM_1 );
        Serial.end();
        tf.kpTape = .25;
    }
    void onLoop() { 
        tf.poll( 190 ); 
    }

    void onEnd() {
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireFirstEwok<tt> 
        return digitalRead( R_CLAW_COMM_OUT ) and millis()-startTime>6000;
    }
};
