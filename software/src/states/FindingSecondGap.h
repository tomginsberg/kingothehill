#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

#ifdef _RIGHT_
    #define PIVOT_TIME 1200
    #define BACK_UP 520
#endif

#ifdef _LEFT_
    #define PIVOT_TIME 1050
    #define BACK_UP 570
#endif

class S_FindingSecondGap: public State {
    uint8_t state = 0;

    const uint16_t SECOND_GAP_BIAS = 0; 
    
    void onLoop() { 
        switch( state ) {
            case 0: {
                Motors::run( -10, 140 );
                delay( PIVOT_TIME );
                Motors::stop();
                delay( 300 );
                LEFT_EDGE_BASELINE  = analogRead( TF_EDGE_LEFT );
                RIGHT_EDGE_BASELINE = analogRead( TF_EDGE_RIGHT );
                Motors::run( 130 );
                delay( 400 );
                state = 5;
                break;
            }
            case 5:
                {
                    if ( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR + SECOND_GAP_BIAS ) { 
                           state = 10;
                           Motors::hardStop();
                           delay(200);
                    } else if (analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR + SECOND_GAP_BIAS ) {
                            state = 20;
                            Motors::hardStop();
                            delay(200);
                    }

                    break;
                }
            
            case 10: 
                {
                    Motors::run( 100, 25 );
                    if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR + SECOND_GAP_BIAS ){
                            Motors::stop();
                            delay(200);
                            state = 40; 
                        }
                    break;
                }

            case 20: 
                {
                    Motors::run( 25, 100 );
                    if( analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR + SECOND_GAP_BIAS ) {
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
        Motors::run(-100,-105);
        delay(BACK_UP);
        Motors::stop();
        delay(200);
    }

    bool transitionCondition() {
        // <tt>DropSecondPlatform<tt> 
        return (state == 40);
    }
};
