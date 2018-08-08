#include <Arduino.h>

#include "../State.h"
#include "../functions/EdgeFollow.h"
#include "../functions/Motors.h"

#define WAIT_TIME 5500
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
        switch(state){
            case 10:{
                ef.poll( 130 );
                if( millis() - startTime > 1000 ) {
                    state = 20;
                }
                break;
            }
            case 20:{
                ef.poll(170);
                if( millis() - startTime > ( WAIT_TIME - AVG_TIME ) ) {
                    avgLeft = ( numReadings * avgLeft + ef.lastLSpeed ) / ( numReadings + 1 );
                    avgRight = ( numReadings * avgRight + ef.lastRSpeed ) / ( numReadings + 1 );
                    numReadings++;
                }
                break;
            }
        }
    }

    void onEnd() {
        Motors::run( avgRight, avgLeft );
    }

    bool transitionCondition() {
            //<tt>SeekingChewbacca<tt>
            return millis() - startTime > WAIT_TIME; 
    }
};
