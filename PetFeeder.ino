#include "HX711.h"
#include <Servo.h> // Library for servo

// Define HX711 pins
const int LOADCELL_DOUT_PIN = A1;
const int LOADCELL_SCK_PIN = A0;

// Define photoresistor pin
const int photoresistorPin = A3;

// Define LED pins
const int led1Pin = 8;

// Distance sensor
const int trigPin = 13;  // Trig Pin
const int echoPin = 12;  // Echo Pin

// Servo
Servo motorServo; // Servo object
const int servoPin = 11; // PWM pin where the servo is connected

// Create HX711 object
HX711 scale;

// Calibration factor (initial adjustable value)
float calibration_factor = -7050;

bool calibrationCompleted = false;

void setup() {
  Serial.begin(9600);
  if (!calibrationCompleted) {
    Serial.println("HX711 Demo");
    Serial.println("------------------");

    // Initialize HX711
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    if (!scale.is_ready()) {
      Serial.println("Error: HX711 is not ready. Check connections!");
      while (1); // Stop execution
    }

    // Reset to zero
    Serial.println("Empty the scale, then press a key to continue.");
    waitForUserInput();
    scale.tare();

    Serial.println("The scale has been reset to zero.");

    // Manual calibration
    Serial.println("Place 1000 grams on the scale, then press a key to continue.");
    waitForUserInput();
    float raw_units = scale.get_units(10);
    calibration_factor = raw_units / 1000.0;
    scale.set_scale(calibration_factor);

    Serial.print("Calibration completed. Calibration factor: ");
    Serial.println(calibration_factor);

    calibrationCompleted = true; // Set the calibration flag
  }

  // Continue initialization
  pinMode(led1Pin, OUTPUT);
  initializeSensor();
  motorServo.attach(servoPin);
}

void loop() {
  // Read weight
  float weight = scale.get_units(10);
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" grams");

  // Read photoresistor value
  int lightLevel = analogRead(photoresistorPin);
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Control LEDs based on brightness
  controlLEDs(lightLevel);

  // Display distance
  float distance = measureDistance(); // Call the distance measurement function
  displayDistance(distance); // Display the distance

  // Servo
  if(distance < 10 && weight < 20) {
    motorServo.write(100);
  } else if (weight >= 20) {
    motorServo.write(70);
  }

  delay(500);
}

// Function to control LEDs based on light level
void controlLEDs(int lightLevel) {
  if (lightLevel > 600) { // High brightness
    digitalWrite(led1Pin, LOW); // LEDs off
  } else { // Low brightness
    digitalWrite(led1Pin, HIGH); // LEDs on
  }
}

// Function to wait for user input
void waitForUserInput() {
  while (Serial.available() > 0) { // Clear serial buffer
    Serial.read();
  }
  while (!Serial.available()) { // Wait for a key press
    delay(10);
  }
  while (Serial.available() > 0) { // Ensure buffer is clean again
    Serial.read();
  }
}

// Distance sensor functions
void initializeSensor() {
  pinMode(trigPin, OUTPUT); // Set Trig pin as OUTPUT
  pinMode(echoPin, INPUT); // Set Echo pin as INPUT
  Serial.println("Sensor ready!");
}

float measureDistance() {
  // Send a 10µs pulse to Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the duration of the signal from Echo (in microseconds)
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = duration * 0.034 / 2;
  return distance; // Return the calculated distance
}

// Function to display distance
void displayDistance(float distance) {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
