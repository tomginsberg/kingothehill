#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"
#include "../functions/TapeFollow.h"

class S_FindTape: public State {
    uint8_t state = 10;
    uint64_t startTime;

    void onStart() {
        startTime = millis();
    }

    void onLoop(){
        switch ( state ) {
            case 10: 
                {
                    //turn right
                    Motors::run( 30, 90 );
                    if ( analogRead(TF_FAR_LEFT)>420 or analogRead(TF_CLOSE_LEFT) > 390 ) {
                        state = 40;
                    } else if( analogRead( TF_EDGE_LEFT ) > 550   and (millis()-startTime>500)) {
                        Motors::stop();
                        delay( 200 );
                        state = 20;
                    }
                    break;
                }
            case 20:
                {
                    //left
                    Motors::run( 90, 30 );
                    if ( analogRead(TF_FAR_LEFT)>420 or analogRead(TF_CLOSE_LEFT) > 390  or analogRead(TF_FAR_RIGHT)>300 ) {
                        Motors::stop();
                        delay(100);
                        Motors::run(20,100);
                        delay(90);
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
