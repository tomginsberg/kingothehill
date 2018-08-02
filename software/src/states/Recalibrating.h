#include <Arduino.h>

#include "../State.h"
#include "../GlobalVariables.h"
#include "../Pins.h"

class S_Recalibrating: public State {
    void onStart() {
        LEFT_EDGE_BASELINE  = analogRead( TF_EDGE_LEFT  );
        RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
     }

    bool transitionCondition() {
        // <tt>FindingSecondGap<tt> 
        return true;
    }
};
