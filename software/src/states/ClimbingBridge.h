#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"

class S_ClimbingBridge: public State {
    EdgeFollower ef;
    
    void onLoop() { 
        ef.poll( 120 );
    }
};
