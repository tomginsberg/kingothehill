#include "../State.h"
#include "../functions/Motors.h"

class S_TestMotor: public State {
    public:
        void onStart() {
            Motors::run( 255, 255 );
        }    
};
