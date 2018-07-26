#pragma once

#include <Arduino.h>

// Arduino Uno (Master)

#define IR_SENSOR 2

#define L_MOTOR_F 5
#define L_MOTOR_B 3
#define R_MOTOR_F 9

#define L_CLAW_COMM_IN 7
#define R_CLAW_COMM_IN 8

#define R_MOTOR_B 10

//// Analog Pins
#define TF_EDGE_LEFT A1
#define TF_EDGE_RIGHT A0
#define TF_FAR_LEFT A2
#define TF_CLOSE_LEFT A3
#define TF_CLOSE_RIGHT A4
#define TF_FAR_RIGHT A5


// Arduino Uno (Slave)

#define L_CLAW_SERVO 11
#define R_CLAW_SERVO 5

#define L_ARM_SERVO 10
#define R_ARM_SERVO 6

#define L_CLAW_COMM_OUT 7
#define R_CLAW_COMM_OUT 8

#define PLATFORM_1 3
#define PLATFORM_2 9

#define STEPPER_1 12
#define STEPPER_2 13

//// Analog Pins
#define L_CLAW_DETECT A0
#define R_CLAW_DETECT A1

void initializePins();

#ifdef _MASTER_
    void initializePins() {
        pinMode( IR_SENSOR, INPUT_PULLUP );
        pinMode( L_MOTOR_F, OUTPUT );
        pinMode( L_MOTOR_B, OUTPUT );
        pinMode( R_MOTOR_F, OUTPUT );
        pinMode( R_MOTOR_B, OUTPUT );
        pinMode( L_CLAW_COMM_IN, INPUT_PULLUP );
        pinMode( R_CLAW_COMM_IN, INPUT_PULLUP );

        pinMode( TF_EDGE_LEFT, INPUT_PULLUP );
        pinMode( TF_EDGE_RIGHT, INPUT_PULLUP );
        pinMode( TF_FAR_LEFT, INPUT_PULLUP );
        pinMode( TF_CLOSE_LEFT, INPUT_PULLUP );
        pinMode( TF_CLOSE_RIGHT, INPUT_PULLUP );
        pinMode( TF_FAR_RIGHT, INPUT_PULLUP );
    }
#endif

#ifdef _SLAVE_
    void initializePins() {
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
    }
#endif
