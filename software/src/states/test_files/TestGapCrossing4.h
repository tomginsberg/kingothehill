#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../Pins.h"

class S_TestGapCrossing4: public State {
    void onStart() {
        Motors::run( 0, 0 );        
        delay( 10 );
        Motors::run( -255, -255 );
        delay( 200 );
        Motors::run( 255, 255 );
        delay( 1000 );
    }

};
