#include "../State.h"
#include <Arduino.h>

class S_Example2: public State {
    // This state causes the built-in light on pin 13 to flash every half-second and has no exit condition

    public:
        void onStart() {
            pinMode( 13, OUTPUT );
        }

        void onLoop() {
            static const uint64_t start_time = millis();
            static const uint32_t flashing_period = 500;  // milliseconds  
            if( ( ( millis() - start_time ) / flashing_period ) % 2 == 0 ) {
                digitalWrite( 13, HIGH );
            } else {
                digitalWrite( 13, LOW );
            }
        }
};
