#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"
#include "../functions/Motors.h"

#ifdef _LEFT_
    #define WAIT_TIME 6700
#endif

#ifdef _RIGHT_
    #define WAIT_TIME 7500
#endif

#define AVG_TIME 1000

class S_ClimbingBridge: public State {
    EdgeFollower ef;
    uint64_t startTime = millis();
    float avgLeft = 0;
    float avgRight = 0;
    uint32_t numReadings = 0;
    uint8_t state = 10;

    void onStart() {
        startTime = millis();
    }

    void onLoop() {
        ef.poll(140);
        // if( millis() - startTime > ( WAIT_TIME - AVG_TIME ) ) {
        //     avgLeft = ( numReadings * avgLeft + ef.lastLSpeed ) / ( numReadings + 1 );
        //     avgRight = ( numReadings * avgRight + ef.lastRSpeed ) / ( numReadings + 1 );
        //     numReadings++;
        // }
    }

    // void onEnd() {
    //     Motors::run( avgRight, avgLeft );
    // }

    bool transitionCondition() {
            //<tt>SeekingChewbacca<tt>
            return millis() - startTime > WAIT_TIME; 
    }
};
