#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"


class S_FindingFirstGap: public State {
    void onStart() {
        //back up
        Motors::run(-50,-50);
        delay(550);

        //rotate clockwise
        Motors::pivot(80,CLOCKWISE);
        delay(250);

        //go forward for a bit 
        Motors::run(90,90);
        delay()

    }

    void onEnd() { 
        Motors::stop();
        delay( 300 );
    }

    bool transitionCondition() {
        // <tt>PositionForDrop<tt> 
        return analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_THR;
    }
};
