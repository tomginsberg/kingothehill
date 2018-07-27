#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"


class S_FindingFirstGap: public State {
    void onStart() {
        //back up
        Motors::run(-70,-70);
        delay(850);

        //rotate clockwise
        Motors::pivot(80,CLOCKWISE);
        delay(550);

        //go forward for a bit 
        Motors::run(60,60);
        delay(950);

        //sweep left
        Motors::run(90,-40);
    }

    void onEnd() { 
        Motors::stop();
        delay( 300 );
    }

    bool transitionCondition() {
        // <tt>PositionForDrop<tt> 
        return analogRead( TF_FAR_LEFT ) > 150;
    }
};
