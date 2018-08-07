#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"
#include "../GlobalVariables.h"

class S_FindingBridgeEdge: public State {
    
    void onStart() { 
        Motors::run( 110 );
        delay( 400 );
        Motors::run( -10, 130 );
    }

    void onEnd() { 
        Motors::stop();
        delay( 500 );
    }

    bool transitionCondition() {
        // <tt>ClimbingBridge<tt> 
        return analogRead( TF_EDGE_RIGHT ) > LEFT_EDGE_BASELINE + 200;
    }
};
