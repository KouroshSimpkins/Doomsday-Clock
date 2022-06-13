// All of the required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "FeedBackServo.h"

// Defines the pin for feedback from the servo, and the control pin.
#define FEEDBACK_SERVO_PIN 2
#define SERVO_PIN 3

// Set the feedback signal pin number
FeedBackServo servo = FeedBackServo(FEEDBACK_SERVO_PIN);

// Sets up the 7 segment display
Adafruit_7segment matrix = Adafruit_7segment();

// A Test value for testing the 7seg display against
int test_value = 2021;

void setup()
{
    // Sets up the 7 segment display  

    matrix.begin(0x70);

    // Sets up the feedback servo
    servo.setServoControl(SERVO_PIN);
    servo.setKp(1);
    Serial.begin(115200);
}

void loop()
{
    servo.rotate(270, 4);
	matrix.print(servo.Angle(), DEC);
    matrix.writeDisplay();
    delay(1000);

    servo.rotate(-180, 4);
    matrix.print(servo.Angle(), DEC);
    matrix.writeDisplay();
    delay(1000);
}
