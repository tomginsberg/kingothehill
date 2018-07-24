#pragma once

#include <Arduino.h>

#include "../SerialIDs.h"

class Platform {
    public:
        virtual void init() = 0;
        virtual void release() = 0;
        virtual void drop() = 0;
};

class FirstPlatform: public Platform {
     public:
        void init() {
            Serial.begin( 9600 );
        };

         void release() {
            uint16_t angle = 150;
            Serial.write( PLATFORM_1_ID );
            Serial.write( ( uint8_t ) ( angle << 8 ) );
            Serial.write( ( uint8_t ) ( angle & 0xFF ) );  
        };

         void drop() {
            uint16_t angle = 0;
            Serial.write( PLATFORM_2_ID );
            Serial.write( ( uint8_t ) ( angle << 8 ) );
            Serial.write( ( uint8_t ) ( angle & 0xFF ) );
        };
};

class SecondPlatform: public Platform {
    public: 
        void init() {
            Serial.begin( 9600 );
        };

        void release() {
            uint16_t angle = 45;
            Serial.write( PLATFORM_1_ID );
            Serial.write( ( uint8_t ) ( angle << 8 ) );
            Serial.write( ( uint8_t ) ( angle & 0xFF ) );  
        };

        void drop() {
            uint16_t angle = 180;
            Serial.write( PLATFORM_2_ID );
            Serial.write( ( uint8_t ) ( angle << 8 ) );
            Serial.write( ( uint8_t ) ( angle & 0xFF ) );
        };
};
