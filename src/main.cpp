#include <Arduino.h>

/**
 * FrisbyRobot.cpp
 * Controller: Seeed Studio XIAO ESP32-C3
 * H-Bridge: L298N (Red Module)
 */

// Function Prototypes (REQUIRED for PlatformIO / C++)
void executeCommand(char cmd);
void moveForward(int speed);
void moveBackward(int speed);
void stopMotors();
void runTestSequence();

// Pin Definitions using XIAO D-numbers
const int ENA = D0; // Motor A Speed (PWM)
const int IN1 = D1; // Motor A Dir 1
const int IN2 = D2; // Motor A Dir 2

const int ENB = D3; // Motor B Speed (PWM)
const int IN3 = D4; // Motor B Dir 1
const int IN4 = D5; // Motor B Dir 2

const int LED_PIN = D10; // Built-in LED on XIAO ESP32-C3

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("--- Frisby Robot (PlatformIO) Initialized ---");
  Serial.println("Commands: F (Forward), B (Backward), S (Stop), T (Test Routine)");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    executeCommand(cmd);
  }
}

void executeCommand(char cmd) {
  switch (toupper(cmd)) {
    case 'F':
      moveForward(200);
      Serial.println("Moving Forward...");
      break;
    case 'B':
      moveBackward(200);
      Serial.println("Moving Backward...");
      break;
    case 'S':
      stopMotors();
      Serial.println("Stopping.");
      break;
    case 'T':
      runTestSequence();
      break;
  }
}

void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  digitalWrite(LED_PIN, LOW); // LED ON
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
  digitalWrite(LED_PIN, HIGH); // LED OFF
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(LED_PIN, HIGH);
}

void runTestSequence() {
  Serial.println("--- Starting Test Routine ---");
  
  Serial.println("Testing Motor A Forward...");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  delay(1500); stopMotors(); delay(500);
  
  Serial.println("Testing Motor A Backward...");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 200);
  delay(1500); stopMotors(); delay(500);
  
  Serial.println("Testing Motor B Forward...");
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 200);
  delay(1500); stopMotors(); delay(500);
  
  Serial.println("Testing Motor B Backward...");
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
  delay(1500); stopMotors(); delay(500);
  
  Serial.println("Testing Both Forward...");
  moveForward(200);
  delay(1500); stopMotors(); delay(500);
  
  Serial.println("Testing Tank Turn...");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
  delay(1500); stopMotors();
  
  Serial.println("--- Test Complete ---");
}
