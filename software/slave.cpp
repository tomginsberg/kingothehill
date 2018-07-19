#include <Arduino.h>
#include "Pins.h"

#include <Servo.h>
#include <Stepper.h>

#define SENSOR_THRESHOLD 400    // Currently arbitrarily set

void setup() {
    Serial.begin( 9600 );

    pinMode( L_CLAW_COMM_OUT, OUTPUT );
    pinMode( R_CLAW_COMM_OUT, OUTPUT );
}


void loop() {
    uint16_t left_arm = analogRead( L_CLAW_DETECT );
    uint16_t right_arm = analogRead( R_CLAW_DETECT );


}
