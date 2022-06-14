// Libraries
#include <Wire.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


File myFile;
String fileName = "test.txt";
int myValue = 100;

String currentLine = "";
String currentVal = "";
String secondVal = "";

int years[29];
int angles[29];


Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
    Serial.begin(9600);

    while (!Serial) {};

    initialiseCard();

    // We only want to read the data from the SD card:
    readFile();

    // To check that the array is loaded correctly for debugging purposes, we write everything to the serial monitor.
    for (int i = 0; i < 29; i++) {
        Serial.print(years[i]);
        Serial.print(", ");
        Serial.println(angles[i]);
    }

    // We now want to display the data on the LED matrix.
    // We need to initialise the LED matrix.
    matrix.begin(0x70);
}

void initialiseCard() {
    Serial.print("Beginning initialization of SD Card: ");

    if (!SD.begin(10)) {
        Serial.println("initialization failed!");
        while (1);
    }

    Serial.println("initialization done."); // <- Reaching this point means the SD card is working.
}

void readFile() {
    myFile = SD.open("test.txt");

    if (myFile) {
        Serial.println("File opened successfully.");
        int i = 0;
        while (myFile.available()) {
            currentLine = myFile.readStringUntil('\n');
            currentVal = currentLine.substring(0, currentLine.indexOf(','));
            secondVal = currentLine.substring(currentLine.indexOf(',') + 1);

            // for the length of the years array, set years[i] to currentVal and angles[i] to secondVal
            if (currentVal.toInt() != 0) {
                years[i] = currentVal.toInt();
                angles[i] = secondVal.toInt();
            }

            // This is not inside a for loop, because myFile.available is a while loop, so the for loop would not work to store the data.

            i++;
        }
        myFile.close();
    } else {
        Serial.println("Error opening file.");
    }
}

void loop() {
    // We want to display the values stored in the years array on the matrix

    for (int i = 0; i < 29; i++) {
        if (years[i] != 0) {
            matrix.print(years[i]);
            matrix.writeDisplay();
            delay(1000);
        }
    }

}
