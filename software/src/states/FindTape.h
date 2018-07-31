#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"

#define RIGHT 0
#define LEFT 1

class S_FindTape: public State {
    uint64_t startTime = millis();
    uint16_t seekTime = 1400;
    uint8_t direction = RIGHT;

    void onStart() { 
        startTime = millis();
        if( direction == RIGHT ) {
            Motors::run( 60, 150 ); 
        } else {
            Motors::run( 150, 60 );
        }
    }

    void onEnd() {
        direction = direction == RIGHT ? LEFT : RIGHT;
        seekTime *= 2;
        Motors::stop(); 
    }

    bool transitionCondition() {
        // <tt>SeekingSecondEwok<tt> 
        return direction == RIGHT ? ( analogRead( TF_CLOSE_LEFT ) > 150 ) : ( analogRead( TF_CLOSE_RIGHT ) > 150 );
    }
    bool alternateCondition() {
        // <tt>FindTape<tt>
        return millis() - startTime > seekTime;
    }
};
