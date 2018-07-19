#include <Arduino.h>

#include "../State.h"

class S_{1}: public State {
    void onStart() { return; }
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
        return false
    }
}
