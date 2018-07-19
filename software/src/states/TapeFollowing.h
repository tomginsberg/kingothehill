#include "../State.h"
#include <Arduino.h>
#include "../functions/TapeFollow.h"

class S_TapeFollowing: public State {
    public:
        void onStart() {
            pinMode( TF_FAR_LEFT, INPUT_PULLUP );
            pinMode( TF_CLOSE_LEFT, INPUT_PULLUP );
            pinMode( TF_CLOSE_RIGHT, INPUT_PULLUP );
            pinMode( TF_FAR_RIGHT, INPUT_PULLUP );
        }

        void onLoop() {
            TapeFollow::poll( 255 );
        }
};
