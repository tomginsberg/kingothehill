#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"


class S_CrossingBridge: public State {
    TapeFollower tf;
    uint64_t startTime;
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_L_CLAW );
        Serial.write( L_CLAW_OUT_OF_WAY );
        delay(1000);
        Motors::run(-40,120);
        delay(400);
        startTime = millis();
    }

    void onLoop()  { 
        tf.poll( 150 ); 
    }

    void onEnd() {
        Motors::stop();
        delay(200);
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>FindTape<tt>
        return millis() - startTime > 1000;
    }
};
