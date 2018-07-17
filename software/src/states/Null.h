#include "../State.h"
#include "../functions/RobotUtils.h"

class S_Null: public State {
    void onStart() {
        RobotUtils::shutdown();
    }
};

