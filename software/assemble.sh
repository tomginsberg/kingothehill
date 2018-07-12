#!/bin/bash

if [ "$1" = "-s" ]
then 
    if [ "$2" = "" ]
    then
        echo "Please provide the name of the state to be loaded."
    elif [ -e "src/states/$2.h" ]
    then
cat <<EOF > src/main.cpp
#include <Arduino.h>
#include "states/$2.h"

State* singleState = new S_$2();

void setup() {
    singleState -> onStart();
}

void loop() {
    singleState -> onLoop();
}
EOF
    else
        echo "\"src/states/$2.h\" was not found..."
    fi
else
    echo "Please provide the \"-s\" option to load a single state."
fi