// All of the required libraries
#include <Wire.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "FeedBackServo.h"
#include <servo.h>


// Setup File stuff
File myFile;
String fileName = "test.txt"; // <- This text file contains the equivalent of Year_And_Time.csv

String currentLine = ""; // <- Contains the currently read line as a string
String yearSplit = ""; // <- Prepared for splitting the currentLine string into year and angle
String angleSplit = ""; 

// These arrays are 29 characters long, the right length for the array given.
// I really did not want to deal with malloc here, so I made the arrays static.
int years[29]; // <- Array of years
int angles[29]; // <- Array of angles

// Defines the pin for feedback from the servo, and the control pin.
#define FEEDBACK_SERVO_PIN 2
#define SERVO_PIN 3

Servo myServo;

// Set the feedback signal pin number
FeedBackServo servo = FeedBackServo(FEEDBACK_SERVO_PIN);

// Sets up the 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();


void setup()
{
    // The first thing to do is setup the SD card reading.
    Serial.begin(9600); // <- Sets the serial port to 9600 baud

    while (!Serial) {}; // <- Waits for the serial port to be ready

    // Initialize the SD card
    initialiseCard();

    readFile();

    for (int i = 0; i < 29; i++)
    {
        Serial.print(years[i]);
        Serial.print(", ");
        Serial.println(angles[i]);
    }

    // Sets up the 7 segment display  
    matrix.begin(0x70);

    // Sets up the feedback servo
    myServo.attach(SERVO_PIN);
    myServo.write(197);
    delay(10000);
}


void initialiseCard() {
    // This function initialises the SD card, and returns any errors to the serial port.
    Serial.print("Beginning initialisation of the SD Card: ");

    if (!SD.begin(10)) { // <- The SD Card is wired into pin 10, so this is the pin number.
        Serial.println("Card failed, or not present");
        while (1); // <- The SD card isn't detected, so we hold the program here.
        // To try again, the program has to be uploaded again.
    }

    Serial.println("Card initialised"); // <- Reaching this point means the SD card is working.
}


void readFile() {
    // This function reads the file, and stores the data in the arrays.

    // Open the file
    myFile = SD.open(fileName);

    // Read the file
    if (myFile) {
        Serial.println("File opened successfully");
        int i = 0;
        while (myFile.available()) {
            currentLine = myFile.readStringUntil('\n');
            yearSplit = currentLine.substring(0, currentLine.indexOf(','));
            angleSplit = currentLine.substring(currentLine.indexOf(',') + 1);

            // for the length of the years array, set years[i] to the value of yearSplit
            // for the length of the angle array, set angles[i] to the value of angleSplit
            if (yearSplit.toInt() != 0) {
                years[i] = yearSplit.toInt();
                angles[i] = angleSplit.toInt();
            }

            i++;
        }
        myFile.close();
    } else {
        Serial.println("Error opening file");
    }
}


void loop()
{
    // This function is the main loop of the program.
    // It reads the file, and then rotates the servo to the correct angle.
    // It also displays the current year on the 7 segment display.
    
    for (int i = 28; i > 0; i--)
    {
        if (years[i] != 0) {
            int realAngle = 183-angles[i];
            myServo.write(realAngle);
            matrix.print(years[i]);
            matrix.writeDisplay();
            delay(5000);
        }
    }
}
