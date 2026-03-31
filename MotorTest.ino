/**
 * MotorTest.ino
 * Routine to test L298N motor driver connections with XIAO ESP32-C3.
 * Spins motors individually and together in both directions.
 */

// Pin Definitions (matching FrisbyRobot.ino)
const int ENA = D0; // Motor A Speed (PWM)
const int IN1 = D1; // Motor A Dir 1
const int IN2 = D2; // Motor A Dir 2

const int ENB = D3; // Motor B Speed (PWM)
const int IN3 = D4; // Motor B Dir 1
const int IN4 = D5; // Motor B Dir 2

const int LED_PIN = D10; // Built-in LED

const int TEST_SPEED = 200; // Speed (0-255)
const int TEST_DELAY = 2000; // 2 seconds per test

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  delay(2000); // Wait for Serial
  Serial.println("=== MOTOR TEST ROUTINE STARTING ===");
  Serial.println("Ensure battery is connected and wheels are clear!");
}

void loop() {
  // --- TEST 1: Motor A Only ---
  Serial.println("Testing Motor A: FORWARD");
  motorA_Forward(TEST_SPEED);
  blinkLED(2);
  delay(TEST_DELAY);
  
  Serial.println("Testing Motor A: BACKWARD");
  motorA_Backward(TEST_SPEED);
  blinkLED(2);
  delay(TEST_DELAY);
  
  stopMotors();
  delay(1000);

  // --- TEST 2: Motor B Only ---
  Serial.println("Testing Motor B: FORWARD");
  motorB_Forward(TEST_SPEED);
  blinkLED(3);
  delay(TEST_DELAY);
  
  Serial.println("Testing Motor B: BACKWARD");
  motorB_Backward(TEST_SPEED);
  blinkLED(3);
  delay(TEST_DELAY);
  
  stopMotors();
  delay(1000);

  // --- TEST 3: Both Together ---
  Serial.println("Testing BOTH: FORWARD");
  motorA_Forward(TEST_SPEED);
  motorB_Forward(TEST_SPEED);
  digitalWrite(LED_PIN, LOW); // LED ON
  delay(TEST_DELAY);
  
  Serial.println("Testing BOTH: BACKWARD");
  motorA_Backward(TEST_SPEED);
  motorB_Backward(TEST_SPEED);
  digitalWrite(LED_PIN, HIGH); // LED OFF
  delay(TEST_DELAY);

  stopMotors();
  delay(1000);

  // --- TEST 4: Tank Turn / Opposite ---
  Serial.println("Testing TANK TURN: A Forward, B Backward");
  motorA_Forward(TEST_SPEED);
  motorB_Backward(TEST_SPEED);
  delay(TEST_DELAY);

  Serial.println("Testing TANK TURN: A Backward, B Forward");
  motorA_Backward(TEST_SPEED);
  motorB_Forward(TEST_SPEED);
  delay(TEST_DELAY);

  stopMotors();
  Serial.println("--- End of Loop, Restarting in 5 seconds ---");
  delay(5000);
}

// --- Helper Functions ---

void motorA_Forward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);
}

void motorA_Backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
}

void motorB_Forward(int speed) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void motorB_Backward(int speed) {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void blinkLED(int times) {
  for(int i=0; i<times; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
  }
}
