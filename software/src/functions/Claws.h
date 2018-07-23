#include <Arduino.h>
#include <Servo.h>

#include "../Pins.h"

class Claw {
    public:
        virtual void init() = 0;
        virtual void liftUp() = 0;
        virtual void liftDown() = 0;
        virtual void openClaw() = 0;
        virtual void closeClaw() = 0;
};

class LeftClaw: public Claw {
    public:
        void init() {
            Serial.begin( 9600 ); 
        }

        void liftUp() {
            Serial.write( L_ARM_SERVO_ID );
            uint16_t angle = 0;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void liftDown() {
            Serial.write( L_ARM_SERVO_ID );
            uint16_t angle = 180;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void openClaw() {
            Serial.write( L_CLAW_SERVO_ID );
            uint16_t angle = 113;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void closeClaw() {
            Serial.write( L_CLAW_SERVO_ID );
            uint16_t angle = 180;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }
};

class RightClaw: public Claw {
    public:
        void init() {
            Serial.begin( 9600 ); 
        }

        void liftUp() {
            Serial.write( R_ARM_SERVO_ID );
            uint16_t angle = 180;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void liftDown() {
            Serial.write( R_ARM_SERVO_ID );
            uint16_t angle = 0;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void openClaw() {
            Serial.write( R_CLAW_SERVO_ID );
            uint16_t angle = 67;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }

        void closeClaw() {
            Serial.write( R_CLAW_SERVO_ID );
            uint16_t angle = 0;
            Serial.write( (uint8_t) (angle >> 8) );
            Serial.write( (uint8_t) (angle & 0xFF)  );
        }
};
