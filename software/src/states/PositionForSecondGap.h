#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"

class S_PositionForSecondGap: public State {
    void onStart() { 
        Motors::pivot( 120, CLOCKWISE );

        return; 
        }

    void onLoop()  { return; }
    void onEnd()   { return; }

    bool transitionCondition() {
        // <tt>TransistionTargetHere<tt> 
        return false;
    }

    bool alternateCondition() {
        // <tt>TransistionTargetHere<tt>
        return false;
    }

    bool errorCondition() {
        // <tt>TransistionTargetHere<tt>
        return false;
    }
};
