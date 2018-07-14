#include <Arduino.h>
#include "../State.h"

#define IR_PIN 2

class S_IRSenseTest: public State {    
    public:
        void onStart() {
            pinMode( IR_PIN, INPUT_PULLUP );
            Serial.begin( 9600 );
        }

        void onLoop() {
            static const uint16_t SAMPLING_TIME = 100;

            static uint64_t samplingStart = millis();
            static bool currentState = digitalRead( IR_PIN );
            static uint32_t numSwitches = 0;

            if( millis() - samplingStart < SAMPLING_TIME ) {
                bool reading = digitalRead( IR_PIN );
                if( currentState != reading ) {
                    numSwitches++;
                    currentState = reading;
                } 
            } else {
                Serial.println( ( numSwitches * ( 1000 / 2 ) ) / SAMPLING_TIME );
                numSwitches = 0;
                samplingStart = millis();
            }


        }

        void onEnd() {
            Serial.end();
        }
};