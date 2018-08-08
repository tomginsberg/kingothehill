#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"
#include "../functions/Motors.h"

#define WAIT_TIME 8050
#define AVG_TIME 2500

class S_ClimbingBridge: public State {
    EdgeFollower ef;
    uint64_t startTime = millis();
    float avgLeft = 0;
    float avgRight = 0;
    uint32_t numReadings = 0;

    void onStart() {
        startTime = millis();
    }

    void onLoop() { 
        ef.poll( 155 );
        if( millis() - startTime > ( WAIT_TIME - AVG_TIME ) ) {
            avgLeft = ( numReadings * avgLeft + ef.lastLSpeed ) / ( numReadings + 1 );
            avgRight = ( numReadings * avgRight + ef.lastRSpeed ) / ( numReadings + 1 );
            numReadings++;
        }
    }

    void onEnd() {
        Motors::run( avgRight, avgLeft+9 );
    }

    bool transitionCondition() {
            //<tt>SeekingChewbacca<tt>
            return millis() - startTime > WAIT_TIME; 
    }
};
