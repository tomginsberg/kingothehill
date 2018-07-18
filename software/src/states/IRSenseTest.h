#include <Arduino.h>
#include "../State.h"
#include "../Pins.h"

class S_IRSenseTest: public State {    
    public:
        void onStart() {
            pinMode( IR_SENSOR, INPUT_PULLUP );
            Serial.begin( 9600 );
        }

        void onLoop() {
            static const uint16_t SAMPLING_TIME = 100;

            static uint64_t samplingStart = millis();
            static uint8_t currentState = digitalRead( IR_SENSOR );
            static uint32_t numSwitches = 0;

            if( millis() - samplingStart < SAMPLING_TIME ) {
                uint8_t reading = digitalRead( IR_SENSOR );
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
