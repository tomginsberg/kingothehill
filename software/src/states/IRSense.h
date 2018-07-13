#include <Arduino.h>
#include "../State.h"

#define IR_PIN 2

class S_IRSense: public State {
    uint32_t currentFrequency = 0;
    
    public:
        void onStart() {
            pinMode( IR_PIN, INPUT_PULLUP );
        }

        void onLoop() {
            static const uint32_t SAMPLING_TIME = 20;

            static uint64_t startTime = millis();
            static bool currentState = digitalRead( IR_PIN );
            static uint32_t numSwitches = 0;

            if( millis() - startTime < SAMPLING_TIME ) {
                bool reading = digitalRead( IR_PIN );
                if( currentState != reading ) {
                    numSwitches++;
                    currentState = reading;
                } 
            } else {
                Serial.begin( 9600 );
                Serial.println( ( numSwitches * ( 1000 / 2 ) ) / SAMPLING_TIME );
                Serial.end();
                numSwitches = 0;
                startTime = millis();
            }


        }

        void onEnd() {
            Serial.end();
        }
};