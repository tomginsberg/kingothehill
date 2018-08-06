#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../SerialIDs.h"

class S_LoweringBasket: public State {
    uint8_t state = 10;

    void onStart() { 
        Motors::run( 100, 110 );
        delay( 1250 );
        Motors::stop();
        delay( 200 );
        Motors::run( -90, 60 );

    }

    void onLoop() {
        switch( state ) {
            case 10: 
            {
                Serial.write( LOWER_BASKET ); 
                if( analogRead( TF_EDGE_RIGHT ) > 850 ) {
                    state = 20;
                    Motors::run( -110 );
                    delay( 1000 );
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
        return state == 20;
    }
};
