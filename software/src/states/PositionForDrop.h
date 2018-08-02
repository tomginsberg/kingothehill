#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../functions/TapeFollow.h"

class S_PositionForDrop: public State {
    TapeFollower tf;
    
    void onStart() {
        Motors::stop();
        delay(80);
        Motors::run( -110); 
        delay( 280 );
    }

    void onEnd()   { 
        Motors::hardStop();
     }

    bool transitionCondition() {
        // <tt>DropFirstPlatform<tt> 
        return true;
    }

};
