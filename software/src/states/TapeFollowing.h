#include "../State.h"
#include <Arduino.h>
#include "../functions/TapeFollow.h"

class S_TapeFollowing: public State {
    public:
        void onStart() {
            pinMode( R_MOTOR_F, OUTPUT );
            pinMode( L_MOTOR_F, OUTPUT );
            pinMode( L_MOTOR_B, OUTPUT );
            pinMode( R_MOTOR_B, OUTPUT );

            pinMode( TF_FAR_LEFT, INPUT_PULLUP );
            pinMode( TF_CLOSE_LEFT, INPUT_PULLUP );
            pinMode( TF_CLOSE_RIGHT, INPUT_PULLUP );
            pinMode( TF_FAR_RIGHT, INPUT_PULLUP );

            Serial.begin( 9600 );
        }

        void onLoop() {
            TapeFollow::poll( 100 );
        }
};
