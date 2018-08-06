#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

class S_CrossBridge2: public State {
    TapeFollower tf;
    uint64_t startTime;
    uint8_t state = 10;

    void onStart() {
        delay(100);
        Motors::run( -100, -110 );
        delay( 320 );
        Motors::run( 110 );
        delay( 500 );
        
        tf.kpTape = 0.28;
    }

    void onLoop()  { 
        switch ( state ) {
            case 10: {
                Motors::run( 10, 100 );
                if ( analogRead( TF_CLOSE_LEFT ) > 150 ) {
                    state = 20;
                    startTime = millis();
                    Motors::stop();
                    delay( 200 );
                }
                break;
            }
            case 20: {
                tf.poll( 160 );
                if ( millis() - startTime > 1800 ) {
                    state = 30;
                    Motors::stop();
                }
                break;
            }    
        }
    }
    
    void onEnd() {
        Motors::hardStop();
        delay(200);
        Motors::run( 120,130 );
        delay( 750 ); 
        Motors::hardStop();
        Serial.begin( 9600 );
        Serial.write( INIT_L_CLAW );
        Serial.write( LOWER_L_CLAW );
        Serial.write( OPEN_L_CLAW );
        delay( 700 );
        Serial.write( DETACH_L_CLAW );
    }

    bool transitionCondition() {
        // <tt>SeekingFourthEwok<tt> 
        return ( state == 30 );
    }

};
