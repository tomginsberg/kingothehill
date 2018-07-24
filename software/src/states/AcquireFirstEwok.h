#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../functions/Claws.h"

class S_AcquireFirstEwok: public State {
    RightClaw right;
    
    void onStart() { 
        Motors::stop();
        right.init();

        right.closeClaw();
        delay( 200 );
        right.liftUp();
        delay( 1000 );
        right.openClaw();
        delay( 200 );
        right.liftDown();
    }


    bool alternateCondition() {
        // <tt>StopAllFunctions<tt>
        return true;
    }
};
