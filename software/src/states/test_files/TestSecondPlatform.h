#include <Arduino.h>

#include "../State.h"
#include "../functions/Platform.h"

class S_TestSecondPlatform: public State {
    SecondPlatform plat;
    void onStart() { 
        plat.attach();
        delay( 1000 );
        plat.release();
        delay( 1000 );
        plat.drop();
    }

};
