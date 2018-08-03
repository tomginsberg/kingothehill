#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_SeekingThirdEwok: public State {
    TapeFollower tf;
    uint64_t startTime;
    uint8_t state = 10;
    bool droppedClaw = false;
    const uint16_t DELAY_TIME = 5000;

    void onStart() { 
        Serial.begin( 9600 );
        tf.kpTape = 0.275;
        startTime = millis();
    }

    void onLoop()  { 
        switch (state){
            case 10:
                {
                    tf.poll( 170 );
                    if( millis() - startTime > DELAY_TIME ) {
                        Motors::stop();
                        delay( 300 );
                        state = 20;
                    }
                    break;

                }
            case 20:
                {
                    Motors::run( 60, 150 );
                    if ( analogRead( TF_FAR_LEFT ) < 90 ) {
                        Motors::stop();
                        delay( 300 );
                        state = 30;
                    }
                    break;
                }

            case 30:
                {
                    Serial.write( INIT_R_CLAW );
                    Serial.write( CLOSE_R_CLAW );
                    Serial.write( LOWER_R_CLAW );
                    

                    Serial.write( INIT_L_CLAW );
                    Serial.write( LOWER_L_CLAW );
                    Serial.write( OPEN_L_CLAW );
                    
                    delay( 1000 );
                    Serial.write( DETACH_R_CLAW );
                    Serial.write( DETACH_L_CLAW );
                    delay(200);
                    Serial.write ( RECALIBRATE );
                    state = 40;
                    break;
                }

            case 40:
                {
                    tf.poll( 140 );
                    if (digitalRead( L_CLAW_COMM_IN )){
                        state = 50;
                    }
                    break;
                }


            }      
    
    }

    void onEnd() {
        Motors::stop();
        Serial.flush();
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>AcquireThirdEwok<tt>
        return (state == 50);
    }
};