#pragma once

#include <Arduino.h>

#define RIGHT_EDGE_DELTA 250
#define LEFT_EDGE_DELTA 300

#define RIGHT_EDGE_THR 780 //Was 880. Measured on first gap: 400-480 on white, 750 on edge, 840 off 
#define LEFT_EDGE_THR 450 //Was 360. Measured on first gap: 90-120 on white, 450 on edge, 550 off

uint16_t LEFT_EDGE_BASELINE;
uint16_t RIGHT_EDGE_BASELINE;
uint16_t SETPOINT;




