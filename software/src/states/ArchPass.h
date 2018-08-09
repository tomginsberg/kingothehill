#include <Arduino.h>

#include "../State.h"
#include "../GlobalVariables.h"
#include "../functions/Motors.h"
#include "../functions/TapeFollow.h"

class S_ArchPass: public State {
    void onStart() {
        Motors::run( 30, 120 );
        delay( 340 );
        Motors::stop();
        delay( 120 );
        Motors::run( 110 );
        delay( 370 );
        Motors::run( 100, -50 );
    }
    
    void onEnd()   { 
        Motors::stop();
        delay( 100 ); 
    }

    bool transitionCondition() {
        // <tt>SeekingThirdEwok<tt> 
       return analogRead(TF_FAR_LEFT)>480;
    }

};
