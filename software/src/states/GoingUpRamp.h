#include <Arduino.h>

#include "../State.h"
#include "../functions/TapeFollow.h"

#define RAMP_SPEED 170

class S_GoingUpRamp: public State {
    TapeFollower tf;
    
    public:
        void onLoop() {
            tf.poll( RAMP_SPEED );
        }

        bool transitionCondition() {
            // <tt>SeekingFirstEwok<tt> 
            return tf.errorDerivative > 200;
        }
};
