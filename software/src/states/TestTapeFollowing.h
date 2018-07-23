#include "../State.h"
#include <Arduino.h>

#include "../functions/TapeFollow.h"

class S_TestTapeFollowing: public State {
    public:
        void onStart() {
            Serial.begin( 9600 );
        }

        void onLoop() {
            TapeFollow::poll();
        }

        void onEnd() {
            Serial.end();
        }
};
