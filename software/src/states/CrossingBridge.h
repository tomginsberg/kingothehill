#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"


class S_CrossingBridge: public State {
    TapeFollower tf;
    uint64_t startTime;
    uint8_t state = 10;
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_L_CLAW );
        Serial.write( LIFT_L_CLAW );
        delay(1000);
        
        startTime = millis();
    }

    void onLoop()  {
        switch (state){
            case 10: 
                {
                    Motors::run( -40, 120 );
                    if (analogRead(TF_CLOSE_LEFT)>120){
                        state = 20;
                        startTime=millis();
                    } 
                    break;
                }
            case 20:
                {
                    tf.poll( 130 );
                    if (millis() - startTime > 900){
                        state = 30;
                    }
                    break;
                }
        } 
        
    }

    void onEnd() {
        Motors::stop();
        delay(800);
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>FindTape<tt>
        return (state == 30);
    }
};
