#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

#define RIGHT 0
#define LEFT 1

class S_FindTape: public State {
    uint8_t state = 10;
    uint64_t sweepTime;

    void onStart() {
        
        sweepTime = millis();
    }
   
    void onLoop(){
        switch ( state ) {
            case 10: 
                {
                    //turn right
                    Motors::run( 40, 100 );
                    if ( analogRead( TF_FAR_LEFT ) > 110 || analogRead( TF_CLOSE_LEFT ) > 110  ) {
                        state = 40;
                    } else if( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR + 150 && ( ( millis() - sweepTime ) > 2000 ) ) {
                        Motors::stop();
                        delay( 200 );
                        state = 20;
                    }
                    break;
                }
            case 20:
                {
                    //left
                    Motors::run( 100, 40 );
                    if ( analogRead( TF_CLOSE_LEFT ) > 110 ) {
                        state = 40;
                    }
                    break;
                }
                
        }
    }
     
    void onEnd() {
        Motors::stop();
        delay( 200 );
    }

    bool transitionCondition() {
        //<tt>SeekingSecondEwok<tt> 
        return (state == 40);
    }
   
};
