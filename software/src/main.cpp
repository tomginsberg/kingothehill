#include <Arduino.h>
#include "states/example_state.h"

State* starting_state = new S_ExampleState();

void setup() {
    starting_state -> on_start();
}

void loop() {
    starting_state -> on_loop();
}
