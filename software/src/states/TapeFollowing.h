#include "../State.h"
#include <Arduino.h>
#include "../functions/TapeFollow.h"

class S_TapeFollowing: public State {
    public:
        void onStart() {
            pinMode( R_MOTOR_F, OUTPUT );
            pinMode( L_MOTOR_F, OUTPUT );
        }

        void onLoop() {
            TapeFollow::poll( 255 );
        }
};
