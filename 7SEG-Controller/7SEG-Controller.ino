#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

int test_value = 2021;
int x = 0;

void setup() {
#ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
#endif
    matrix.begin(0x70);
    
    Wire.begin(9);
    Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
    x = Wire.read();
}

void loop() {
    matrix.print(x);
    matrix.writeDisplay();
    delay(1000);
    test_value++;
}