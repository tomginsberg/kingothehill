#include "../state.h"
#include <Arduino.h>

class S_ExampleState: public State {
    public:
        void on_start() {
            pinMode( 13, OUTPUT );
        }

        void on_loop() {
            static const uint64_t start_time = millis();
            static const uint32_t flashing_period = 1000;  // milliseconds  
            if( ( ( millis() - start_time ) / flashing_period ) % 2 == 0 ) {
                digitalWrite( 13, HIGH );
            } else {
                digitalWrite( 13, LOW );
            }
        }

        void on_end() {}
};