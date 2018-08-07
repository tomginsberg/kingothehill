#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"
#include "../GlobalVariables.h"

class S_FindingBridgeEdge: public State {
    uint16_t state = 10;

    void onStart() { 
        Motors::run( 110 );
        delay( 400 );
        Motors::run( -10, 130 );
    }

    void onLoop() {
        switch( state ) {
            case 10: 
            {
                if( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_THR ) {
                    state = 20;
                    Motors::run( -10, 130 );
                }
            }
        }
    }

    void onEnd() { 
        Motors::stop();
        delay( 500 );
    }

    bool transitionCondition() {
        // <tt>ClimbingBridge<tt> 
        return state == 20 && analogRead( TF_EDGE_RIGHT ) > LEFT_EDGE_BASELINE + 200;
    }
};
