#pragma once

#include <Arduino.h>
#include <Servo.h>

#include "../SerialIDs.h"
#include "../Pins.h"


class Platform {
    public:
        virtual void init() = 0;
        virtual void release() = 0;
        virtual void drop() = 0;
        virtual void detach() = 0;
};

class FirstPlatform: public Platform {
     Servo releaser;
     Servo dropper;
     
     public:
        void init() {
            releaser.attach( PLATFORM_1 );
            dropper.attach( PLATFORM_2 );
        };

        void release() {
            releaser.write( 150 );
        };

        void drop() {
            dropper.write( 0 );
        };

        void detach() {
            releaser.detach();
            dropper.detach();
        }
};

class SecondPlatform: public Platform {
    Servo releaser;
    Servo dropper;

    public:
        void init() {
            releaser.attach( PLATFORM_1 );
            dropper.attach( PLATFORM_2 );
        };

        void release() {
            releaser.write( 45 );
        };

        void drop() {
            dropper.write( 180 );
        };

        void detach() {
            releaser.detach();
            dropper.detach();
        }
};
