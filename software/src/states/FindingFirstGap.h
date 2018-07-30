#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"


class S_FindingFirstGap: public State {
    void onStart() {
        //back up
        Motors::run( -130 );
        delay( 850 );

        //rotate clockwise
        Motors::pivot( 150, CLOCKWISE );
        delay( 350 );

        //go forward for a bit 
        Motors::run( 110 );
        delay( 950 );

        //sweep left
        Motors::run( 170, -70 );
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
