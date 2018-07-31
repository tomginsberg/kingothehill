#include <Arduino.h>

#include "../State.h"
#include "../GlobalVariables.h"
#include "../functions/Motors.h"

class S_ArchPass: public State {
    void onStart() {
        Motors::run(170,-70);
    }
    
    void onEnd()   { 
        Motors::stop();
        delay(100); 
    }

    bool transitionCondition() {
        // <tt>SeekingThirdEwok<tt> 
       return analogRead( TF_FAR_LEFT ) > 150;
    }

};
