#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../Pins.h"
#include "../SerialIDs.h"

#include "../functions/Claws.h"

class S_TestServo: public State {   
    LeftClaw claw;

    void onStart() {
        claw.init();
    }

    void onLoop() {
        claw.openClaw();
        delay( 600 );
        claw.closeClaw();
    }
};
