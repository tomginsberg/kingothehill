#include <Arduino.h>
#include <Servo.h>

#include "../State.h"
#include "../Pins.h"
#include "../SerialIDs.h"

#include "../functions/Claws.h"

class S_TestServo: public State {   
    RightClaw claw;

    void onStart() {
        claw.init();
        claw.closeClaw();
        claw.liftUp();
    }
};
