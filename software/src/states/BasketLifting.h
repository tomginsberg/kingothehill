#include "../State.h"
#include <Arduino.h>
#include <Stepper.h>
int STEPS_PER_REV = 500;

class S_BasketLifting: public State {
    public:
        void onStart() {
            Stepper stepper = Stepper(STEPS_PER_REV,12,13);
            liftBasket();
            // Do something like drive forward until a switch is triggered
            dropBasket();
        }

        void onLoop() {
            
        }
        
        void liftBasket() {
            stepper.setSpeed(1200);
            for (int i = 0; i < 13; i++)
              stepper.step(10025);
        }
        
        void dropBasket() {
            stepper.setSpeed(1200);
            for (int i = 0; i < 13; i++)
              stepper.step(-10025);
        }
};
