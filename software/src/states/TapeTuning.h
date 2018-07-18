#include "../State.h"
#include "../functions/TapeFollower.h"

#include <Arduino.h>
#include <CurieBLE.h>


#define LED 13

class S_TapeTuning: public State {
    const char uuid[37]  = "81EB0000-2DB1-4997-9FA1-1DBE44215A4D";
    
    const char uuidProperty1[37] = "81EB0001-2DB1-4997-9FA1-1DBE44215A4D";
    const char uuidProperty2[37] = "81EB0002-2DB1-4997-9FA1-1DBE44215A4D";
    const char uuidProperty3[37] = "81EB0003-2DB1-4997-9FA1-1DBE44215A4D";
    const char uuidProperty4[37] = "81EB0004-2DB1-4997-9FA1-1DBE44215A4D";
 
    TapeFollower tf;
    
    BLEPeripheral myBoard;
    BLEService constantFetcher = uuid;
       
    BLECharCharacteristic    kpChar{ uuidProperty1, BLERead | BLEWrite };
    BLECharCharacteristic    kdChar{ uuidProperty2, BLERead | BLEWrite };
    BLECharCharacteristic    kiChar{ uuidProperty3, BLERead | BLEWrite };
    BLECharCharacteristic speedChar{ uuidProperty4, BLERead | BLEWrite } ;

    int8_t kp = 128;
    int8_t kd = 0;
    int8_t ki = 0;

    int8_t speed = 0;

    public:
        void onStart() {
            pinMode( RIGHT_MOTOR_F, OUTPUT );
            pinMode(  LEFT_MOTOR_F, OUTPUT );
            
            pinMode( LED, OUTPUT );

            myBoard.setLocalName( "The Sex Panther" );
            myBoard.setAdvertisedServiceUuid( constantFetcher.uuid() );

            myBoard.addAttribute( constantFetcher );

            myBoard.addAttribute( kpChar );
            myBoard.addAttribute( kdChar );
            myBoard.addAttribute( kiChar );
            myBoard.addAttribute( speedChar );

            kpChar.setValue( kp );
            kdChar.setValue( kd );
            kiChar.setValue( ki );

            speedChar.setValue( speed );

            tf.setConstants( kp, kd, ki );
            tf.setSpeed( speed );

            myBoard.begin();
        }

        void onLoop() {
            digitalWrite( LED, HIGH );
            BLECentral central = myBoard.central();
            
            if( central ) {
                digitalWrite( LED, LOW );
                while( central.connected() ) {
                    tf.poll();
                    if( kpChar.written() ) {
                        kp = kpChar.value();
                        tf.setConstants( kp, kd, ki );
                    } 
                    if( kdChar.written() ) {
                        kd = kdChar.value();
                        tf.setConstants( kp, kd, ki );
                    }
                    if( kiChar.written() ) {
                        ki = kiChar.value();
                        tf.setConstants( kp, kd, ki );
                    }
                    if( speedChar.written() ) {
                        speed = speedChar.value();
                        tf.setSpeed( speed );
                    }
                }
            }
        }
};
