#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include "arduino_secrets.h"

/**
 * FrisbyRobot.cpp
 * Controller: Seeed Studio XIAO ESP32-C3
 * UI Bridge: Web Server based remote control (Sacred Modern Command Center)
 */

// Function Prototypes
void handleRoot();
void handleMove();
void handleStop();
void handleTest();
void moveForward(int speed);
void moveBackward(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void stopMotors();
void runTestSequence();

// --- CONFIGURATION ---
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

WebServer server(80);

// Pin Definitions using XIAO D-numbers
const int ENA = D0; const int IN1 = D1; const int IN2 = D2;
const int ENB = D3; const int IN3 = D4; const int IN4 = D5;
const int LED_PIN = D10;

void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  
  // CONNECT TO WIFI
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  // Blink LED while connecting
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
  }
  
  Serial.println("\n--- Frisby Robot ONLINE ---");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_PIN, LOW); // Solid ON when connected

  // INITIALIZE mDNS (frisby.local)
  if (MDNS.begin("frisby")) {
    Serial.println("mDNS responder started: frisby.local");
  }

  // WEB SERVER ROUTES
  server.on("/", handleRoot);
  server.on("/move", handleMove);
  server.on("/stop", handleStop);
  server.on("/test", handleTest);
  
  // CORS Enable (for Browser UI)
  server.enableCORS();
  
  server.begin();
  Serial.println("Web Server Started.");
}

void loop() {
  server.handleClient();
  
  // Also keep Serial control available
  if (Serial.available() > 0) {
    char cmd = toupper(Serial.read());
    if (cmd == 'F') moveForward(200);
    else if (cmd == 'B') moveBackward(200);
    else if (cmd == 'S') stopMotors();
    else if (cmd == 'T') runTestSequence();
  }
}

// --- HANDLERS ---
void handleRoot() { 
  server.send(200, "text/plain", "Frisby Robot Online"); 
}

void handleMove() {
  String dir = server.arg("dir");
  int speed = server.arg("speed").toInt();
  if (speed == 0) speed = 150;

  if (dir == "F") {
    moveForward(speed);
    server.send(200, "text/plain", "Moving Forward");
  } else if (dir == "B") {
    moveBackward(speed);
    server.send(200, "text/plain", "Moving Backward");
  } else if (dir == "L") {
    turnLeft(speed);
    server.send(200, "text/plain", "Turning Left");
  } else if (dir == "R") {
    turnRight(speed);
    server.send(200, "text/plain", "Turning Right");
  } else {
    server.send(400, "text/plain", "Invalid Direction");
  }
}

void handleStop() {
  stopMotors();
  server.send(200, "text/plain", "Stopped");
}

void handleTest() {
  server.send(200, "text/plain", "Starting Routine...");
  runTestSequence();
}

// --- MOTOR LOGIC ---
void moveForward(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, speed);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, speed);
  digitalWrite(LED_PIN, LOW); // Active Low LED ON
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, speed);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, speed);
  digitalWrite(LED_PIN, HIGH); // LED OFF
}

void turnLeft(int speed) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, speed);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, speed);
}

void turnRight(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, speed);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, speed);
}

void stopMotors() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(LED_PIN, HIGH);
}

void runTestSequence() {
  Serial.println("--- Starting Test Routine ---");
  moveForward(200); delay(1000); stopMotors(); delay(500);
  moveBackward(200); delay(1000); stopMotors();
  Serial.println("--- Test Complete ---");
}
