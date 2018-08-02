#include <Arduino.h>

#include "../State.h"
#include "../SerialIDs.h"
#include "../functions/Motors.h"

class S_DropSecondPlatform: public State {
        void onStart() { 
        Serial.begin( 9600 );

        Serial.write( INIT_PLATFORM_2 );
        Serial.write( RELEASE_PLATFORM_2 );
        delay( 40 );
        Serial.write( DROP_PLATFORM_2 );
        delay( 1000 );
    }

    void onEnd() {
        Serial.write( DETACH_PLATFORM_2 );
        Serial.write( INIT_PLATFORM_1 );
        delay( 300 );
        Serial.write( DETACH_PLATFORM_1 );
        Serial.flush();
        Serial.end();        
    }


    bool transitionCondition() {
        // <tt>CrossBridge2<tt> 
        return true;
    }

  
};
