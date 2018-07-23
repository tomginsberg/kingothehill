#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../Pins.h"

class S_TestServo: public State {
    Servo myServo;
    
    void onStart() {
        myServo.attach( R_ARM_SERVO );
        Serial.begin( 9600 ); 
        myServo.write( 180 );
    }

    void onLoop()  { 
        static bool attached = true;
        if( Serial.available() >= 1 ) {
            Serial.read();
            if( attached ) {
                myServo.detach();
            } else {
                myServo.attach( R_ARM_SERVO );
            }
            attached = !attached;
            Serial.println( attached );
        }
    }
};
