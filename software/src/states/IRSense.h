#include <Arduino.h>
#include "../State.h"

#include "../Pins.h"

class S_IRSense: public State {
    uint16_t currentFrequency = 0;
    uint64_t startTime;
    
    public:
        void onStart() {
            startTime = millis();
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
                currentFrequency = ( numSwitches * ( 1000 / 2 ) ) / SAMPLING_TIME;
                numSwitches = 0;
                samplingStart = millis();
            }


        }

        bool transistionCondition() {
            // <tt>TapeFollowing<tt>
            static const uint16_t FREQUENCY_CUTOFF = 9000;

            return currentFrequency > FREQUENCY_CUTOFF;
        }

        bool errorCondition() {
            // <tt>TapeFollowing<tt>
            static const uint16_t MAX_WAITING_TIME = 20000;
            
            return millis() - startTime > MAX_WAITING_TIME;
        }
};
