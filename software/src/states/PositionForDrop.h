#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../functions/TapeFollow.h"

class S_PositionForDrop: public State {
    TapeFollower tf;
    
    void onStart() { 
        Motors::run(-70,-70);
        delay(700);
    }

    void onEnd()   { 
        Motors::stop();
     }

    bool transitionCondition() {
        // <tt>DropFirstPlatform<tt> 
        return true;
    }

};
