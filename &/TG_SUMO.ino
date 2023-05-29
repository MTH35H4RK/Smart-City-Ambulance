#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(13, 12); // RX, TX pins

const int MOTOR_A_ENA = 3; // right motor
const int MOTOR_A_IN1 = 2;
const int MOTOR_A_IN2 = 5;
const int MOTOR_B_IN3 = 4;
const int MOTOR_B_IN4 = 7;
const int MOTOR_B_ENB = 6; // left motor

void forward(int speed) {
  analogWrite(MOTOR_A_ENA, speed);
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_B_ENB, speed);
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
}
void Fturn(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
}
void Bturn(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}


void backward(int speed) {
  analogWrite(MOTOR_A_ENA, speed);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speed);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}


void stop() {
  analogWrite(MOTOR_A_ENA, 0);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_B_ENB, 0);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, LOW);
}

void setup() {
  // Set the motor pins as output
  pinMode(MOTOR_A_ENA, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_ENB, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);

  // Set the baud rate for Bluetooth communication
    bluetoothSerial.begin(9600);

}

void loop() {
  if (bluetoothSerial.available()) {
    char command = bluetoothSerial.read();

    switch (command) {
      case 'F':
        forward(255); // Forward
        break;
      case 'B':
        backward(255); // Backward
        break;
      case 'L':
        Fturn(255,0); // Turn Left
        break;
      case 'R':
        Fturn(0,255); // Turn Right
        break;
      case 'G':
        Fturn(255,100); // Forward Left
        break;
      case 'I':
        Fturn(100,255); // Forward Right
        break;
      case 'H':
        Bturn(100,255); // Backward Left
        break;
      case 'J':
        Bturn(255,100); // Backward Right
        break;
      case 'S':
        stop();
        break;
      default:
        break;
    }
  }
}
