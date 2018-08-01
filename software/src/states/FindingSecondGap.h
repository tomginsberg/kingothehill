#include <Arduino.h>

#include "../State.h"
#include "../functions/Motors.h"
#include "../GlobalVariables.h"

#define EDGE_THRESHOLD 100

class S_FindingSecondGap: public State {
    uint8_t state = 0;
    
    void onLoop() { 
        switch( state ) {
            case 0: {
                Motors::run( 60, 125 );
                delay( 800 );
                Motors::stop();
                Motors::run( 110 );
                while( analogRead( TF_EDGE_LEFT )  < LEFT_EDGE_BASELINE  + EDGE_THRESHOLD && 
                       analogRead( TF_EDGE_RIGHT ) < RIGHT_EDGE_BASELINE + EDGE_THRESHOLD ) {

                    /* Waiting... */ 
                }
                Motors::hardStop();
                if( LEFT_EDGE_BASELINE > analogRead( TF_EDGE_LEFT )  + EDGE_THRESHOLD ) {
                    state = 10;
                } else {
                    state = 20;
                }
                break;
            }

            case 10: {
                Motors::run( 90, 60 );
                while( analogRead( TF_EDGE_RIGHT ) < RIGHT_EDGE_BASELINE + EDGE_THRESHOLD ) {
                    // Waiting...
                }
                Motors::stop();
                state = 40;
                break;
            }

            case 20: {
                Motors::run( 90, 60 );
                while( analogRead( TF_EDGE_LEFT ) < LEFT_EDGE_BASELINE + EDGE_THRESHOLD ) {
                    // Waiting...
                }
                Motors::stop();
                state = 40;
                break;
            }
        }
    }

    bool transitionCondition() {
        // <tt>StopAllFunctions<tt> 
        return state == 40;
    }
};
