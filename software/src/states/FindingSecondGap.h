#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

class S_FindingSecondGap: public State {
    uint8_t state = 0;
    
    void onLoop() { 
        switch( state ) {
            case 0: {
                Motors::run( -10, 140 );
                delay( 830 );
                Motors::stop();
                delay(300);
                LEFT_EDGE_BASELINE  = analogRead( TF_EDGE_LEFT  );
                RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
                Motors::run( 130 );
                delay(400);
                state = 5;
                break;
            }
            case 5:
                {
                    if ( analogRead( TF_EDGE_LEFT )  > LEFT_EDGE_BASELINE  + LEFT_EDGE_THR)
                        { 
                       
                           state = 10;
                           Motors::hardStop();
                           delay(200);
                       }
                    else if (analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + RIGHT_EDGE_THR)
                        {
                            state = 20;
                            Motors::hardStop();
                            delay(200);
                        }

                    break;
                }
            
            case 10: 
                {
                    Motors::run( 80, 20 );
                    if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_BASELINE + RIGHT_EDGE_THR ){
                            Motors::stop();
                            delay(200);
                            state = 40; 
                        }
                    break;
                }

            case 20: 
                {
                    Motors::run( 20, 80 );
                    if( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_BASELINE + LEFT_EDGE_THR ) {
                        Motors::stop();
                        delay(200);
                        state = 40;
                    }
                    break;
                }
            
        }
    }

    void onEnd() {
        delay(200);
        Motors::run(-100,-100);
        delay(500);
        Motors::stop();
        delay(200);
    }

    bool transitionCondition() {
        // <tt>DropSecondPlatform<tt> 
        return (state == 40);
    }
};
