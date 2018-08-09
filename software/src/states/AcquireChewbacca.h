#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../SerialIDs.h"

class S_AcquireChewbacca: public State {
    void onStart() { 
        Serial.begin( 9600 );
        Serial.write( INIT_L_CLAW );
        Serial.write( CLOSE_L_CLAW );
        delay( 1200 );
        Serial.write(EWOK_PUSH);
        delay(200);
        Serial.write(EWOK_PULL);
        delay(200);
        Serial.write(PUSHER_DETACH);
        delay(50);
        Serial.write( LIFT_L_CLAW );
        delay( 2000 );
        Serial.write( LEFT_CLAW_OPEN_WIDE );
        delay( 1200 );
        Serial.write( LOWER_L_CLAW );
        delay( 700 );
    }

    void onEnd() {
        Serial.write( DETACH_L_CLAW );
        Serial.flush();
        Serial.end();
    }


    bool transitionCondition() {
        // <tt>RaisingBasket<tt>
        return true;
    }
};
