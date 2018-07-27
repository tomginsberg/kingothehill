#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingThirdEwok: public State {
    TapeFollower tf;
    uint64_t startTime;
    bool droppedClaw = false;
    const uint16_t DELAY_TIME = 4000;

    void onStart() { 
        Serial.begin( 9600 );

        startTime = millis();
    }

    void onLoop()  { 
        tf.poll( 120 ); 
        if( millis() - startTime > DELAY_TIME && !droppedClaw ) {
            Serial.write( INIT_R_CLAW );
            Serial.write( LIFT_R_CLAW );
            Serial.write( OPEN_R_CLAW );
            Serial.write( DETACH_R_CLAW );
            Serial.write( INIT_L_CLAW );
            Serial.write( LIFT_L_CLAW );
            Serial.write( OPEN_L_CLAW );

            droppedClaw = true;
        }
    }

    void onEnd() {
        Motors::stop();

        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }
};