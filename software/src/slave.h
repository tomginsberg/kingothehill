#include <Arduino.h>

#include <Stepper.h>
#include <Servo.h>

#include "Pins.h"
#include "SerialIDs.h"
#include "functions/Claws.h"
#include "functions/Platform.h"

#define STEPS_PER_REV 500

#define L_CLAW_DELTA 45
#define R_CLAW_DELTA 75

Stepper stepper = Stepper( STEPS_PER_REV, STEPPER_1, STEPPER_2 );

LeftClaw left;
RightClaw right;

FirstPlatform first;
SecondPlatform second;

uint16_t CLAW_THRESHOLD_L;
uint16_t CLAW_THRESHOLD_R;

int currentSpeed = 1200;
int speedIntervals = 20;
long steps = 110000;
int intervals = 100;
int maxSpeed = 2500;

int dv;
long ds;

void setup() {
    initializePins();

    Serial.begin( 9600 );

    delay( 1000 );
    
    digitalWrite( RESET_CONTROL, HIGH );

    CLAW_THRESHOLD_L = analogRead( L_CLAW_DETECT ) + L_CLAW_DELTA;  
    CLAW_THRESHOLD_R = analogRead( R_CLAW_DETECT ) + R_CLAW_DELTA;

    stepper.setSpeed( currentSpeed );
    dv = (maxSpeed-currentSpeed)/speedIntervals;
    ds=steps/intervals;
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

            //raise 25%
            case RAISE_BASKET_A_BIT: {
                ds = (int((steps*.25) / 10));
                for( int i = 0; i < 10; i++ ) {
                    stepper.step( ds );
                }
                break;
            }

            //raise 75%
            case RAISE_BASKET_THE_REST: {
                ds = (int((steps*.75) / 10));
                for( int i = 0; i < 10; i++ ) {
                    stepper.step( ds );
                }
                break;
            }

            //lower 15%
            case LOWER_BASKET_TO_MID: {
                ds = -(int((steps*.15) / 10));
                for( int i = 0; i < 10; i++ ) {
                    stepper.step( ds );
                }
                break;
            }

            //lower 85%
            case LOWER_BASKET_FROM_MID: {
                ds = -(int((steps*.85) / 10));
                for( int i = 0; i < 10; i++ ) {
                    stepper.step( ds );
                }
                break;
            }

            case LOWER_BASKET: {
                ds = -steps / intervals;
                for (int i=0; i<intervals; i++){
                    stepper.step(ds);
                    if (i==intervals/10){
                        delay(6000);
                        }
                }
                break;
            }

            case RAISE_BASKET_MASTER: {
                ds = steps / intervals;
                for (int i=0; i<intervals; i++){
                    stepper.step(ds);
                    if (i<speedIntervals){
                        currentSpeed+=dv;
                        }
                    stepper.setSpeed(currentSpeed);
                }
                stepper.setSpeed(1200);
                break;
            }

            case RECALIBRATE: {
                CLAW_THRESHOLD_L = analogRead( L_CLAW_DETECT ) + L_CLAW_DELTA;  
                CLAW_THRESHOLD_R = analogRead( R_CLAW_DETECT ) + R_CLAW_DELTA;
                break;
            }

            case LEFT_CLAW_OPEN_WIDE: {
                left.openWide();
                break;
            }

            case DETACH_L_ARM: {
                left.detachArm();
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
