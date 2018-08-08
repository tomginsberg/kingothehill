#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"
#include "../GlobalVariables.h"

class S_SeekingFourthEwok: public State {
    int state = 10;
    
    void onLoop() { 
        Motors::run( -10, 130 );

        if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR ) {
            state = 20;
            Motors::run( 100, 50 );
            delay( 500 );
        }
    }

    void onEnd() { 
        Motors::hardStop(); 
    }

    bool transitionCondition() {
        // <tt>AcquireFourthEwok<tt> 
        return digitalRead( L_CLAW_COMM_IN );
    }

    bool errorCondition() {
        // <tt>FindingBridgeEdge<tt>
        return state == 20;   
    }
};
