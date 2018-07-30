#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../functions/TapeFollow.h"

class S_PositionForDrop: public State {
    TapeFollower tf;
    
    void onStart() {
        Motors::run( -120 ); 
        delay( 220 );
    }

    void onEnd()   { 
        Motors::hardStop();
     }

    bool transitionCondition() {
        // <tt>DropFirstPlatform<tt> 
        return true;
    }

};
