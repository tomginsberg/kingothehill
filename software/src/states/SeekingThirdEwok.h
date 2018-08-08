#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"
#include "../SerialIDs.h"
#include "../GlobalVariables.h"

class S_SeekingThirdEwok: public State {
    TapeFollower tf;
    uint64_t startTime;
    uint8_t state = 10;
    bool droppedClaw = false;
    const uint16_t DELAY_TIME = 5500;

    void onStart() { 
        Serial.begin( 9600 );
        tf.kpTape = 0.38;
        startTime = millis();
    }

    void onLoop()  { 
        switch (state){
            case 10:
                {
                    tf.poll( 125 );
                    if( millis() - startTime > DELAY_TIME ) {
                        Motors::hardStop();
                        delay( 300 );
                        state = 30;
                    }
                    break;

                }
            case 20:
                {
                    if (analogRead( TF_CLOSE_LEFT ) > 150){
                        Motors::stop();
                        delay( 100 );
                        state = 30;
                        tf.kpTape=0.29;
                    }
                    else{
                        Motors::run( 50, 110 );
                    }
                    break;
                }

            case 30:
                {
                    Serial.write( INIT_R_CLAW );
                    Serial.write( CLOSE_R_CLAW );
                    Serial.write( LOWER_R_CLAW );
                    
                    delay( 1000 );

                    Serial.write( INIT_L_CLAW );
                    Serial.write( LOWER_L_CLAW );
                    Serial.write( OPEN_L_CLAW );
                    
                    delay( 1000 );
                    Serial.write( DETACH_R_CLAW );
                    Serial.write( DETACH_L_CLAW );
                    delay(200);
                    Serial.write ( RECALIBRATE );
                    state = 40;
                    tf.kdTape = 0;
                    break;
                }

            case 40:
                {
                    tf.poll( 110 );
                    if ( digitalRead( L_CLAW_COMM_IN ) ) {
                        state = 50;
                    } else if ( analogRead( TF_EDGE_RIGHT ) > RIGHT_EDGE_THR && analogRead( TF_EDGE_LEFT ) > LEFT_EDGE_THR ) {
                        Motors::hardStop();
                        delay(200);
                        state = 60;
                    }
                    break;
                }
            
            case 60: 
            {
                Serial.begin( 9600 );
                Serial.write( INIT_L_CLAW );
                Serial.write( CLOSE_L_CLAW );
                delay( 1200 );
                Serial.write( LIFT_L_CLAW );
                delay( 1500 );
                Serial.write( OPEN_L_CLAW );
                delay( 1000 );
                Serial.write( DETACH_L_CLAW );
                Serial.flush();
                Serial.end();
                Motors::run(-100,-110);
                delay(600);
                Motors::stop();
                state=70;
                break;

            }   
        }   
    
    }

    void onEnd() {
        Motors::stop();
        Serial.flush();
        Serial.end();
    }

    bool transitionCondition() {
        // <tt>AcquireThirdEwok<tt>
        return (state == 50);
    }

    bool errorCondition() {
        //<tt>FindingSecondGap<tt>
        return (state == 70);
    }
};
