#pragma once

#include <Arduino.h>
#include <Servo.h>

#include "../Pins.h"
#include "../SerialIDs.h"

class Claw {
    public:
        virtual void init() = 0;
        virtual void liftUp() = 0;
        virtual void liftDown() = 0;
        virtual void openClaw() = 0;
        virtual void closeClaw() = 0;
        virtual void detach() = 0;
};

class LeftClaw: public Claw {
    Servo claw;
    Servo arm;
    
    public:
        void init() {
            claw.attach( L_CLAW_SERVO );
            arm.attach( L_ARM_SERVO );
        }

        void liftUp() {
            arm.write( 0 );
        }

        void liftDown() {
            arm.write( 180 );
        }

        void openClaw() {
            claw.write( 83 );
        }

        void closeClaw() {
            claw.write( 180 );
        }

        void detach() {
            arm.detach();
            claw.detach();
        }

        void outOfWay() {
            arm.write( 35 );
            closeClaw();
        }
};

class RightClaw: public Claw {
    Servo claw;
    Servo arm;
    
    public:
        void init() {
            claw.attach( R_CLAW_SERVO );
            arm.attach( R_ARM_SERVO );
        }

        void liftUp() {
            arm.write( 180 );
        }

        void liftDown() {
            arm.write( 0 );
        }

        void openClaw() {
            claw.write( 180 );
        }

        void closeClaw() {
            claw.write( 65 );
        }

        void detach() {
            arm.detach();
            claw.detach();
        }
};
