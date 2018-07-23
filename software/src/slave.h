#include <Arduino.h>

#include <Stepper.h>
#include <Servo.h>

#include "Pins.h"
#include "SerialIDs.h"

#define STEPS_PER_REV 500
#define CLAW_THRESHOLD 400 // Currently arbitrary

Servo servos[6];
Stepper stepper = Stepper( STEPS_PER_REV, STEPPER_1, STEPPER_2 );

void setup() {
    initializePins();

    servos[L_CLAW_SERVO_ID].attach( L_CLAW_SERVO );
    servos[R_CLAW_SERVO_ID].attach( R_CLAW_SERVO );
    servos[L_ARM_SERVO_ID].attach( L_ARM_SERVO );
    servos[R_ARM_SERVO_ID].attach( R_ARM_SERVO );
    servos[PLATFORM_1_ID].attach( PLATFORM_1 );
    servos[PLATFORM_2_ID].attach( PLATFORM_2 );

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
        
        uint16_t value = ( buff[1] << 8 ) | buff[2];
        switch( buff[0] ) {
            case L_CLAW_SERVO_ID: servos[buff[0]].write( value );
            case R_CLAW_SERVO_ID: servos[buff[0]].write( value );
            case L_ARM_SERVO_ID: servos[buff[0]].write( value );
            case R_ARM_SERVO_ID: servos[buff[0]].write( value );
            case PLATFORM_1_ID: servos[buff[0]].write( value );
            case PLATFORM_2_ID: servos[buff[0]].write( value );
            case STEPPER_UP_ID: stepper.step( value );
            case STEPPER_DOWN_ID: stepper.step( -value );
            case STEPPER_HOME_ID: break; // TODO
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
