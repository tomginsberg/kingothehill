#include "../State.h"
#include <Arduino.h>

#include "../functions/TapeFollow.h"

class S_TestTapeFollowing: public State {
    TapeFollower tf;
    
    public:
        void onLoop() {
            tf.poll( 160 );
        }
};
