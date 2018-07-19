#include <Arduino.h>

#include "../State.h"

class S_{1}: public State {
    void onStart() { return; }
    void onLoop()  { return; }
    void onEnd()   { return; }

    bool transitionCondition() {
        return false;
    }

    bool alternateCondition() {
        return false;
    }

    bool errorCondition() {
        return false
    }
}
