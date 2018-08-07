#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"
#include "../functions/Motors.h"

class S_DropFirstPlatform: public State {
    void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_PLATFORM_1 );
        delay( 40 );
        Serial.write( RELEASE_PLATFORM_1 );
        delay( 40 );
        Serial.write( DROP_PLATFORM_1 );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( DETACH_PLATFORM_1 );
        Serial.flush();
        Serial.end();
        Motors::run( -130 );
        delay( 200 );
        Motors::stop();
        
        Motors::run( 100, 120 );
        delay( 1000 );
        Motors::stop();
    }

    bool transitionCondition() {
        //<tt>CrossingBridge<tt>
        return true;
    }
};
