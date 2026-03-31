/**
 * FrisbeeRobot.ino
 * All code snippets and prompts are provided "as-is" under the Apache 2.0 License. 
 * While the technical barriers to coding are lower, the responsibility for security, 
 * compliance (including HIPAA/GDPR), and output accuracy remains strictly with the human-in-the-loop. 
 * Copyright 2026 Thiago Borba Onofre, Licensed under the Apache License, Version 2.0
 * 
 * Controller: Seeed Studio XIAO ESP32-C3
 * H-Bridge: L298N (Red Module)
 * 
 * Instructions:
 * 1. Remove ENA/ENB jumpers on L298N.
 * 2. Connect XIAO D0 to ENA and D3 to ENB.
 * 3. Connect DIR pins as defined below.
 */

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
  Serial.println("--- Frisbee Robot Initialized ---");
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
  digitalWrite(LED_PIN, LOW); // LED ON (Active Low)
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
  
  // Motor A Forward
  Serial.println("Testing Motor A Forward...");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  delay(1500); stopMotors(); delay(500);
  
  // Motor A Backward
  Serial.println("Testing Motor A Backward...");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 200);
  delay(1500); stopMotors(); delay(500);
  
  // Motor B Forward
  Serial.println("Testing Motor B Forward...");
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 200);
  delay(1500); stopMotors(); delay(500);
  
  // Motor B Backward
  Serial.println("Testing Motor B Backward...");
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
  delay(1500); stopMotors(); delay(500);
  
  // Both Forward
  Serial.println("Testing Both Forward...");
  moveForward(200);
  delay(1500); stopMotors(); delay(500);
  
  // Different Directions (Tank Turn)
  Serial.println("Testing Opposite Directions (A Forw, B Back)...");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
  delay(1500); stopMotors();
  
  Serial.println("--- Test Complete ---");
}
