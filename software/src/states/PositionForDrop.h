#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../functions/TapeFollow.h"

class S_PositionForDrop: public State {
    TapeFollower tf;
    
    void onStart() { 
        //
        Motors::run(90,-50);
        delay(400);
    }

    void onLoop() {
        tf.poll( 75 );
    }
    
    void onEnd()   { 
        Motors::run(-50,-50);
        delay(1000);
        Motors::stop();
        delay(300);
     }

    bool transitionCondition() {
        // <tt>DropFirstPlatform<tt> 
        return 
        analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_THR &&
        analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + RIGHT_EDGE_THR;
    }

};
