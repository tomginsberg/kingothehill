#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

#define RIGHT 0
#define LEFT 1

class S_FindTape: public State {
    uint64_t startTime = millis();
    uint16_t seekTime = 50;
    uint16_t index = 1;
    uint8_t direction = LEFT;
    uint8_t state =10;

    
    void onEnd() {
        Motors::stop();
        delay(200);
    }

    void onLoop(){
        switch (state){
            case 10: 
                {
                    //turn right
                    Motors::run(-150,170);
                    if ( analogRead( TF_FAR_LEFT > 110 ) ) {
                        state = 40;
                    }
                    else if( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + 400 ) {
                        Motors::stop();
                        delay( 200 );
                        state = 20;
                    }
                    break;
                }
            case 20:
                {
                    //left
                    Motors::run(130,30);
                    if (analogRead(TF_CLOSE_LEFT)>110){
                        state = 40;
                    }
                    break;
                }
                
        }
    }

    bool transitionCondition() {
        //<tt>SeekingSecondEwok<tt> 
        return (state==40);
    }
   
};
