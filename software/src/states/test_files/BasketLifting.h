#include "../State.h"
#include <Arduino.h>
#include <Stepper.h>
#include "../Pins.h"

int STEPS_PER_REV = 500;

class S_BasketLifting: public State {
    public:
        void onStart() {
            Stepper stepper = Stepper( STEPS_PER_REV, STEPPER_1, STEPPER_2 );
            stepper.setSpeed(1200);
            liftBasket(stepper);
            // Do something like drive forward until a switch is triggered
            dropBasket(stepper);
        }

        void onLoop() {
            
        }
        
        void liftBasket(Stepper stepper) {
            for (int i = 0; i < 13; i++)
              stepper.step(10025);
        }
        
        void dropBasket(Stepper stepper) {
            for (int i = 0; i < 13; i++)
              stepper.step(-10025);
        }
};
