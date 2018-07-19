#pragma once

#include <Arduino.h>

// Genuino 101 (Master)

#define IR_SENSOR 2

#define R_MOTOR_F 3
#define R_MOTOR_B 5
#define L_MOTOR_F 6

#define L_CLAW_COMM_IN 7
#define R_CLAW_COMM_IN 8

#define L_MOTOR_B 9

//// Analog Pins
#define TF_EDGE_LEFT A0
#define TF_EDGE_RIGHT A1
#define TF_FAR_LEFT A2
#define TF_CLOSE_LEFT A3
#define TF_CLOSE_RIGHT A4
#define TF_FAR_RIGHT A5


// Arduino Uno (Slave)

#define L_CLAW_SERVO 3
#define R_CLAW_SERVO 5

#define L_ARM_SERVO 6
#define R_ARM_SERVO 9

#define L_CLAW_COMM_OUT 7
#define R_CLAW_COMM_OUT 8

#define PLATFORM_1 10
#define PLATFORM_2 11

#define STEPPER_1 12
#define STEPPER_2 13

//// Analog Pins
#define L_CLAW_DETECT A0
#define R_CLAW_DETECT A1
