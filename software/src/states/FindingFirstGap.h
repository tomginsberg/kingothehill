#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"


class S_FindingFirstGap: public State {
    void onStart() {
        //back up
        Motors::run( -130 );
        delay( 550 );

        Motors::stop();
        delay(200);

        //rotate clockwise
        Motors::pivot( 150, CLOCKWISE );
        delay( 350 );

        Motors::stop();
        delay(200);

        //go forward for a bit 
        Motors::run( 110 );
        delay( 900 );

        Motors::stop();
        delay(200);
        
        //sweep left
        Motors::run( 150, -70 );
    }

    void onEnd() { 
        Motors::stop();
        delay( 1500 );
    }

    bool transitionCondition() {
        // <tt>PositionForDrop<tt> 
        return analogRead( TF_FAR_LEFT ) > 150;
    }
};
