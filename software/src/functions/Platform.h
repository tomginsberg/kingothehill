#pragma once

#include <Arduino.h>
#include <Servo.h>

#include "../SerialIDs.h"
#include "../Pins.h"


class Platform {
    public:
        virtual void init() = 0;
        virtual void attach() = 0;
        virtual void release() = 0;
        virtual void drop() = 0;
        virtual void detach() = 0;
};

class FirstPlatform: public Platform {
     Servo releaser;
     Servo dropper;
     
     public:
        void init() {
            attach();
            releaser.write( 0 );
            dropper.write( 85 );
        }

        void attach() {
            releaser.attach( PLATFORM_1 );
            dropper.attach( PLATFORM_2 );
        };

        void release() {
            releaser.write( 180 );
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
            attach();
            releaser.write( 150 );
            dropper.write( 0 );
        }

        void attach() {
            releaser.attach( PLATFORM_1 );
            dropper.attach( PLATFORM_2 );
        };

        void release() {
            releaser.write( 45 );
        };

        void drop() {
            dropper.write( 175 );
        };

        void detach() {
            releaser.detach();
            dropper.detach();
        }
};
