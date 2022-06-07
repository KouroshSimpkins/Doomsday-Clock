#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

int test_value = 2021;

void setup()
{
	#ifndef __AVR_ATtiny85__
        Serial.begin(9600);
        Serial.println("7 Segment Backpack Test");
    #endif
    matrix.begin(0x70);
}

void loop()
{
	matrix.print(test_value, DEC);
    matrix.writeDisplay();
    delay(150);

    matrix.print("7SEG");
    matrix.writeDisplay();
    delay(150);
}
