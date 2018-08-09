#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"

#ifdef _LEFT_
    #define FORWARD_TIME 1250
#endif

#ifdef _RIGHT_
    #define FORWARD_TIME 1400
#endif

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
        
        tf.kpTape = 0.16;
        tf.disableOutsideSensors();
    }

    void onLoop()  { 
        switch ( state ) {
            case 10: {
                Motors::run( 10, 100 );
                if ( TapeFollower::onBlack( TF_CLOSE_RIGHT ) ) {
                    state = 20;
                    startTime = millis();
                    Motors::stop();
                    delay( 500 );
                }
                break;
            }
            case 20: {
                tf.poll( 170 );
                if ( millis() - startTime > 1600 ) {
                    state = 30;
                }
                break;
            }    
        }
    }
    
    void onEnd() {
        Motors::run( 110, 140 );
        delay( FORWARD_TIME ); 
        Motors::stop();
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
