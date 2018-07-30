#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"
#include "../functions/Motors.h"

class S_DropFirstPlatform: public State {
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_PLATFORMS );
        delay( 40 );
        Serial.write( RELEASE_PLATFORM_1 );
        delay( 40 );
        Serial.write( DROP_PLATFORM_1 );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( DETACH_PLATFORMS );
        Serial.flush();
        Serial.end();
        Motors::run( -130 );
        delay( 300 );
        Motors::stop();
    }

    bool transitionCondition() {
        //<tt>SeekingSecondEwok<tt>
        return true;
    }
};
