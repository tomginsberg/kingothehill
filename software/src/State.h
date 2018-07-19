#pragma once

class State {
    public:
        virtual void onStart() { return; }
        virtual void onLoop()  { return; }
        virtual void onEnd()   { return; }

        virtual bool transitionCondition() {
            return false;
        }

        virtual bool alternateCondition() {
            return false;
        }

        virtual bool errorCondition() {
            return false;
        }
};


