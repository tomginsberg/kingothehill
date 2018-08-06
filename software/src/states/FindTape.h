#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

#define RIGHT 0
#define LEFT 1

class S_FindTape: public State {
    uint8_t state = 10;
    uint64_t sweepTime = millis();
    
    void onEnd() {
        Motors::stop();
        delay( 200 );
    }

    void onLoop(){
        switch ( state ) {
            case 10: 
                {
                    //turn right
                    Motors::run( 60, 140 );
                    if ( analogRead( TF_FAR_LEFT ) > 110 || analogRead( TF_CLOSE_LEFT ) > 110  ) {
                        state = 40;
                    } else if( analogRead( TF_EDGE_RIGHT ) > 920 && ((millis()-sweepTime)>2000)) {
                        Motors::stop();
                        delay( 200 );
                        state = 20;
                    }
                    break;
                }
            case 20:
                {
                    //left
                    Motors::run( 130, 30 );
                    if ( analogRead( TF_CLOSE_LEFT ) > 110 ) {
                        state = 40;
                    }
                    break;
                }
                
        }
    }

    bool transitionCondition() {
        //<tt>SeekingSecondEwok<tt> 
        return (state == 40);
    }
   
};
