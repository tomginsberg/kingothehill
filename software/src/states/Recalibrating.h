#include <Arduino.h>

#include "../State.h"
#include "../GlobalVariables.h"

class S_Recalibrating: public State {
    void onStart() { }

    bool transitionCondition() {
        // <tt>SeekingSecondGap<tt> 
        return true;
    }
};
