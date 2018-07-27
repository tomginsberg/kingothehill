#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../Pins.h"

class S_TestGapCrossing2: public State {
    Servo platform1;
    Servo platform2;
    
    void onStart() { 
        platform1.attach( PLATFORM_1 );
        platform2.attach( PLATFORM_2 );

        platform1.write( 150 );
        platform2.write( 0 );

        delay( 5000 );

        platform1.write( 45 );

        delay( 30 );

        platform2.write( 180 );
    }
};
