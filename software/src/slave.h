#include <Arduino.h>

#include <Stepper.h>
#include <Servo.h>

#include "Pins.h"

#define STEPS_PER_REV 500
#define CLAW_THRESHOLD 400 // Currently arbitrary

Servo servos[6];
Stepper stepper = Stepper( STEPS_PER_REV, STEPPER_1, STEPPER_2 );

void setup() {
    pinMode( L_CLAW_SERVO, OUTPUT );
    pinMode( R_CLAW_SERVO, OUTPUT );

    pinMode( L_ARM_SERVO, OUTPUT );
    pinMode( R_ARM_SERVO, OUTPUT );

    pinMode( L_CLAW_COMM_OUT, OUTPUT );
    pinMode( R_CLAW_COMM_OUT, OUTPUT );

    pinMode( PLATFORM_1, OUTPUT );
    pinMode( PLATFORM_2, OUTPUT );

    pinMode( STEPPER_1, OUTPUT );
    pinMode( STEPPER_2, OUTPUT );

    pinMode( L_CLAW_DETECT, INPUT_PULLUP );
    pinMode( R_CLAW_DETECT, INPUT_PULLUP );

    servos[0].attach( L_CLAW_SERVO );
    servos[1].attach( R_CLAW_SERVO );
    servos[2].attach( L_ARM_SERVO );
    servos[3].attach( R_ARM_SERVO );
    servos[4].attach( PLATFORM_1 );
    servos[5].attach( PLATFORM_2 );

    Serial.begin( 9600 );

    stepper.setSpeed( 1200 );    
}

void loop() {
    if( Serial.available() >= 3 ) {
        // At each write, the slave expects 3 bytes with the following protocol
        // 1 - TargetID ( Left Claw Servo = 0x00 )
        //              ( Right Claw Servo = 0x01 )
        //              ( Left Arm Servo = 0x02 )
        //              ( Right Arm Servo = 0x03 )
        //              ( First Platform Servo = 0x04 )
        //              ( Second Platform Servo = 0x05 )
        //              ( Stepper {Advancing Upwards} = 0x06 )
        //              ( Stepper {Advancing Downwards} = 0x07 )
        //              ( Stepper {Find Home} = 0x08 )
        // 
        // 23 - TargetValue ( An unsigned 2 byte integer representing an angle or a number of steps ) 
        
        uint8_t buff[3];

        Serial.readBytes( buff, 3 );
        
        if( buff[0] < 0x06 ) {
            uint16_t angle = ( buff[1] << 8 ) + buff[2];
            servos[buff[0]].write( angle );
        } else {
            uint16_t steps = ( buff[1] << 8 ) + buff[2];
            switch( buff[0] ) {
                case 0x06: stepper.step( steps );
                case 0x07: stepper.step( -steps );
                case 0x08: break; // TODO
            }
        }
    }

    if( analogRead( L_CLAW_DETECT ) > CLAW_THRESHOLD ) {
        digitalWrite( L_CLAW_COMM_OUT, HIGH );
    } else {
        digitalWrite( L_CLAW_COMM_OUT, LOW  );
    }
    
    if( analogRead( R_CLAW_DETECT ) > CLAW_THRESHOLD ) {
        digitalWrite( R_CLAW_COMM_OUT, HIGH );
    } else {
        digitalWrite( R_CLAW_COMM_OUT, LOW  );
    }
}
