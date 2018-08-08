#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../Pins.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../SerialIDs.h"

class S_SeekingFirstEwok: public State {
    TapeFollower tf;
    uint64_t startTime;

    const uint32_t WAIT_TIME = 5500;
    
    void onStart() {
        startTime = millis();

        LEFT_EDGE_BASELINE = analogRead( TF_EDGE_LEFT );
        RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );

        Serial.begin( 9600 );
        Serial.write( INIT_PLATFORM_1 );
        delay( 300 );
        Serial.write( DETACH_PLATFORM_1 );
        Serial.end();
        tf.kpTape = 0.30;    //old .23
    }

    void onLoop() { 
        tf.poll( 190 );
        //old 170 
    }

    void onEnd() {
        Motors::hardStop();
    }

    bool transitionCondition() {
        // <tt>AcquireFirstEwok<tt> 
        return digitalRead( R_CLAW_COMM_OUT ) && ( millis() - startTime ) > WAIT_TIME;
    }
};
