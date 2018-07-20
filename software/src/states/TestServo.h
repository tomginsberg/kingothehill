#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../Pins.h"

class S_TestServo: public State {
    Servo myServo;
    
    void onStart() {
        myServo.attach( 3 );
        Serial.begin( 9600 ); 
        myServo.write( 0 );
    }

    void onLoop()  { 
        if( Serial.available() >= 1 ) {
            uint8_t angle = Serial.read();
            myServo.write( angle );
            Serial.println( angle );
        }
    }
};
