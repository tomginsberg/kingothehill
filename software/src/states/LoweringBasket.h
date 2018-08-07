#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_LoweringBasket: public State {
    uint8_t state = 10;

    void onStart() { 
        Motors::run( 70, 150 );
        delay( 1050 );
        Motors::run(-100,-115);
        delay(300);
        Motors::stop();
        delay( 200 );
        Motors::run( -90, 60 );

    }

    void onLoop() {
        switch( state ) {
            case 10: 
            {
                Serial.write( LOWER_BASKET );
                state = 20;
                break;
            }
            case 30: {
                if( analogRead( TF_EDGE_RIGHT ) > 870 ) {
                    state = 20;
                    Motors::run( -100,-115 );
                    delay( 950 );
                }
                break;
            }
        }
    }

    void onEnd() {
          
         Motors::stop();
         
    }

    bool transitionCondition() {
        // <tt>StopAllFunctions<tt> 
        return state == 30;
    }
};
