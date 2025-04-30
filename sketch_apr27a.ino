#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pins (using PWM pins for smooth fading)
const int greenLED = 10;
const int yellowLED = 9;
const int redLED = 3;  // Changed to PWM pin

bool lecturesCompleted = false;

void showMessage(String line1, String line2, int delayTime) {
  lcd.clear();
  delay(300); // smooth clearing
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(delayTime);
}

void blinkYellow(int blinkCount, int blinkDelay) {
  for (int i = 0; i < blinkCount; i++) {
    digitalWrite(yellowLED, HIGH);
    delay(blinkDelay);
    digitalWrite(yellowLED, LOW);
    delay(blinkDelay);
  }
}

void lectureSequence(String subject, String locationTime, bool specialConductedBy = false) {
  // Green: Lecture starting soon
  digitalWrite(greenLED, HIGH);
  showMessage(subject + " in", "", 4500);
  digitalWrite(greenLED, LOW);
  delay(400);

  // Yellow: Lecture ongoing
  digitalWrite(yellowLED, HIGH);
  showMessage(locationTime, "", 8000);
  
  if (specialConductedBy) {
    delay(500);
    showMessage("Conducted By", "Prof.Ruchit Soni", 4500);
  }
  
  digitalWrite(yellowLED, LOW);
  delay(400);

  // Yellow blinking: Lecture about to end
  showMessage(subject, "is About to End", 5000);
  blinkYellow(5, 600);

  // Red: Lecture over
  analogWrite(redLED, 255);  // Full brightness for red LED
  showMessage(subject, "Lecture is Over", 4500);
  analogWrite(redLED, 0);  // Turn off red LED
  delay(500);
}

void setup() {
  // LED setup
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);  // Using PWM capable pin for smooth fading

  // Initialize LEDs to OFF
  analogWrite(greenLED, 0);
  analogWrite(yellowLED, 0);
  analogWrite(redLED, 0);

  // LCD setup
  lcd.init();
  lcd.backlight();

  // Intro messages
  showMessage("WELCOME TO", "INDUS UNIVERSITY", 4500);
  delay(400);
  showMessage("Good Morning", "CSE-B1 Batch", 4500);
  delay(500);

  // Lecture sequences
  showMessage("Your First", "Lecture is", 4000);
  lectureSequence("BST-GLM", "LH-B002 at 9:55");

  showMessage("Your Second", "Lecture is", 4000);
  lectureSequence("DELA-RSM", "LH-B002 at 10:50");

  showMessage("Your Third", "Lecture is", 4000);
  lectureSequence("EP-RS", "LH-B002 at 12:40");

  showMessage("Your Fourth", "Lecture is", 4000);
  lectureSequence("PPS-ZV", "LH-03 at 12:40");

  // Break time
  showMessage("You have a", "BREAK NOW!!", 4500);
  delay(27000);

  // Post-break lectures
  showMessage("Your Fifth and", "Sixth Lecture is", 4000);
  lectureSequence("B1-WPE", "B-327 at 14:25", true);

  showMessage("Your Seventh and", "Last Lecture is", 4000);
  lectureSequence("BAC-VC", "LH-38 at 16:05");

  // Final messages
  delay(8000);
  showMessage("All the Lectures", "Completed", 4500);
  lecturesCompleted = true;  // Set the flag to true when all lectures are completed

  showMessage("See You", "Tomorrow!", 4500);
}

void loop() {
  // After lectures are completed, LEDs start breathing effect
  if (lecturesCompleted) {
    for (int brightness = 0; brightness <= 255; brightness += 5) {
      analogWrite(greenLED, brightness);
      analogWrite(yellowLED, brightness);
      analogWrite(redLED, brightness);
      delay(20);
    }
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
      analogWrite(greenLED, brightness);
      analogWrite(yellowLED, brightness);
      analogWrite(redLED, brightness);
      delay(20);
    }
  }
}

