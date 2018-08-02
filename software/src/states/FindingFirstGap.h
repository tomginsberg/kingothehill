#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"


class S_FindingFirstGap: public State {
    void onStart() {
        //back up
        Motors::run( -100 );
        delay( 550 );

        Motors::stop();
        delay(200);

        //rotate clockwise
        Motors::pivot( 120, CLOCKWISE );
        delay( 350 );

        Motors::stop();
        delay(200);

        //go forward for a bit 
        Motors::run( 90 );
        delay( 900 );

        Motors::stop();
        delay(200);
        
        //sweep left
        Motors::run( 120, -50 );
    }

    void onEnd() { 
        Motors::stop();
        delay( 200 );
    }

    bool transitionCondition() {
        // <tt>PositionForDrop<tt> 
        return analogRead( TF_FAR_LEFT ) > 150;
    }
};
