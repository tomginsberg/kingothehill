#include <Arduino.h>

#include <Stepper.h>
#include <Servo.h>

#include "Pins.h"
#include "SerialIDs.h"
#include "functions/Claws.h"
#include "functions/Platform.h"

#define STEPS_PER_REV 500

Stepper stepper = Stepper( STEPS_PER_REV, STEPPER_1, STEPPER_2 );

LeftClaw left;
RightClaw right;

FirstPlatform first;
SecondPlatform second;

uint16_t CLAW_THRESHOLD_L;
uint16_t CLAW_THRESHOLD_R;

void setup() {
    initializePins();

    Serial.begin( 9600 );

    stepper.setSpeed( 1200 );  

    delay( 1000 );
    
    digitalWrite( RESET_CONTROL, HIGH );

    CLAW_THRESHOLD_L = analogRead( L_CLAW_DETECT ) + 160;  
    CLAW_THRESHOLD_R = analogRead( R_CLAW_DETECT ) + 160;
}

void loop() {
    if( Serial.available() >= 1 ) {
        uint8_t action = Serial.read();

        switch( action ) {
            case INIT_L_CLAW: {
                left.init();              
                break;
            }
            case OPEN_L_CLAW: {
                left.openClaw();             
                break;
            }
            case CLOSE_L_CLAW: {
                left.closeClaw();               
                break;
            }
            case LIFT_L_CLAW: {
                left.liftUp();             
                break;
            }
            case LOWER_L_CLAW: {
                left.liftDown();
                break;
            }
            case L_CLAW_OUT_OF_WAY: {
                left.outOfWay();
                break;
            }
            case DETACH_L_CLAW: {
                left.detach();
                break;
            }

            case INIT_R_CLAW: {
                right.init();              
                break;
            }
            case OPEN_R_CLAW: {
                right.openClaw();             
                break;
            }
            case CLOSE_R_CLAW: {
                right.closeClaw();               
                break;
            }
            case LIFT_R_CLAW: {
                right.liftUp();             
                break;
            }
            case LOWER_R_CLAW: {
                right.liftDown();
                break;
            }
            case DETACH_R_CLAW: {
                right.detach();
                break;
            }

            case INIT_PLATFORM_1: {
                first.init();
                break;
            }
            case RELEASE_PLATFORM_1: {
                first.release();
                break;
            }
            case DROP_PLATFORM_1: {
                first.drop();
                break;
            }
            case DETACH_PLATFORM_1: {
                first.detach();
                break;
            }

            case INIT_PLATFORM_2: {
                second.init();
                break;
            }
            case RELEASE_PLATFORM_2: {
                second.release();
                break;
            }
            case DROP_PLATFORM_2: {
                second.drop();
                break;
            }
            case DETACH_PLATFORM_2: {
                second.detach();
                break;
            }

            case RAISE_BASKET: {
                for( int i = 0; i < 5; i++ ) {
                    stepper.step( 26065 );
                }
                break;
            }

            case LOWER_BASKET: {
                for( int i = 0; i < 5; i++ ) {
                    stepper.step( -26065 );
                }
                break;
            }

            case RECALIBRATE: {
                CLAW_THRESHOLD_L = analogRead( L_CLAW_DETECT ) + 100;  
                CLAW_THRESHOLD_R = analogRead( R_CLAW_DETECT ) + 90;
                break;
            }
        }
    }

    if( analogRead( L_CLAW_DETECT ) > 80 ) {
        digitalWrite( L_CLAW_COMM_OUT, HIGH );
    } else {
        digitalWrite( L_CLAW_COMM_OUT, LOW  );
    }
    
    if( analogRead( R_CLAW_DETECT ) > CLAW_THRESHOLD_R ) {
        digitalWrite( R_CLAW_COMM_OUT, HIGH );
    } else {
        digitalWrite( R_CLAW_COMM_OUT, LOW  );
    }
}
