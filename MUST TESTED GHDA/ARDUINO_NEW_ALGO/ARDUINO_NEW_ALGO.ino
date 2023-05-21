int LDR_Pin = A0;
int m = 0;
int LED = 0;
String response = "";
// Motor pins
const int MOTOR_A_ENA = 10; // this is right motor
const int MOTOR_A_IN1 = 9;
const int MOTOR_A_IN2 = 8;
const int MOTOR_B_IN3 = 7;
const int MOTOR_B_IN4 = 6;
const int MOTOR_B_ENB = 5; // this is left motor

// Define the pins for the TCRT5000L sensor
int sensorPin1 = A1;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorPin4 = A4;
int sensorPin5 = A5;

// Define the threshold values for the sensors
int threshold = 500;

String getResponse() {
  String response = "";
  while (Serial.available() > 0) {
    response += char(Serial.read());
  }
  response.trim();
  return response;
}
String getr() {
  while (response != "A1_H1_V11" && response != "A1_H1_V12" && response != "A2_H1_V11" && response != "A2_H1_V12" && response != "A2_H2_V21" && response !=  "A2_H2_V22" && response != "A1_H2_V21" && response != "A1_H2_V22") {
    response = getResponse();
    Serial.print("getting the response:");
    Serial.print(response);
    Serial.println(",");
  }
  return response;
}

void setup() {

  // initialize serial:
  Serial.begin(115200);
  while (!Serial);

  delay(1000);                    // Wait for the ESP to start

  Serial.println("");
  Serial.println("Arduino started");

  response = getr();

  // Set the motor pins as output
  pinMode(MOTOR_A_ENA, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_ENB, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);

  // Set the sensor pins as input
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
  pinMode(LDR_Pin, INPUT);

}
void forward(int speed) {
  analogWrite(MOTOR_A_ENA, speed);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speed);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}
void turn(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}


void hardturnright(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
}
void hardturnleft(int speedA, int speedB) {
  analogWrite(MOTOR_A_ENA, speedA);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_B_ENB, speedB);
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
}
void right() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);
  turn(0, 200);
  // Check if the robot is on the line
  if (sensorValue1 < threshold && sensorValue2 < threshold && sensorValue3 < threshold && sensorValue4 < threshold && sensorValue5 < threshold) {
    // Stop the robot
    turn(0, 255); //turn right slightly
  } else {
    // Calculate the position of the robot on the line

    int position = 0;

    if (sensorValue3 < threshold) {
      position = 3;
    }
    if (sensorValue2 < threshold) {
      position = 2;
    }

    if (sensorValue1 < threshold) {
      position = 1;
    }
    if (sensorValue4 < threshold) {
      position = 4;
    }
    if (sensorValue5 < threshold) {
      position = 5;
    }


    // Adjust the motor speed and direction based on the position
    if (position == 1) {
      // Turn left
      hardturnleft(255, 255);

    } else if (position == 2) {
      turn(255, 0);
    } else if (position == 3) {
      // Go straight
      forward(255);
    } else if (position == 4) {
      // Turn right slightly
      turn(0, 255);
    } else if (position == 5) {

      // Turn right
      hardturnright(255, 255);


    }
  }
}
void left() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);
  // Check if the robot is on the line
  if (sensorValue1 < threshold && sensorValue2 < threshold && sensorValue3 < threshold && sensorValue4 < threshold && sensorValue5 < threshold) {
    // Stop the robot
    turn(255, 0); //turn left slightly
  }
  if (sensorValue1 > threshold && sensorValue2 > threshold && sensorValue3 > threshold && sensorValue4 > threshold && sensorValue5 > threshold) {
    // Stop the robot
    turn(255, 100); //turn left slightly
  }
  else {
    // Calculate the position of the robot on the line

    int position = 0;

    if (sensorValue3 < threshold) {
      position = 3;
    }
    if (sensorValue4 < threshold) {
      position = 4;
    }
    if (sensorValue5 < threshold) {
      position = 5;
    }
    if (sensorValue2 < threshold) {
      position = 2;
    }

    if (sensorValue1 < threshold) {
      position = 1;
    }



    // Adjust the motor speed and direction based on the position
    if (position == 1) {
      // Turn left
      hardturnleft(255, 255);

    } else if (position == 2) {
      turn(255, 0);
    } else if (position == 3) {
      // Go straight
      forward(255);
    } else if (position == 4) {
      // Turn right slightly
      turn(0, 255);
    } else if (position == 5) {

      // Turn right
      hardturnright(255, 255);


    }
  }
}
void V12() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);
  // Check if the robot is on the line

  if (sensorValue1 < threshold && sensorValue2 < threshold && sensorValue3 < threshold && sensorValue4 < threshold && sensorValue5 < threshold) {
    // Stop the robot
    hardturnright(100, 255);
  }

  else {
    // Calculate the position of the robot on the line

    int position = 0;

    if (sensorValue3 < threshold) {
      position = 3;
    }
    if (sensorValue2 < threshold) {
      position = 2;
    }

    if (sensorValue1 < threshold) {
      position = 1;
    }
    if (sensorValue4 < threshold) {
      position = 4;
    }
    if (sensorValue5 < threshold) {
      position = 5;
    }
    if (sensorValue4 < threshold && sensorValue5 < threshold) {
      position = 6;
    }


    // Adjust the motor speed and direction based on the position
    if (position == 1) {
      // Turn left
      hardturnleft(255, 255);

    } else if (position == 2) {
      turn(255, 0);
    } else if (position == 3) {
      // Go straight
      forward(255);
    } else if (position == 4) {
      // Turn right slightly
      turn(0, 255);
    } else if (position == 5) {
      // Turn right
      hardturnright(255, 255);
    }
    else if (position == 6) {
      // forward?
      forward(210);
    }
  }

}
void V22() {
  // Read the sensor values
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);
  turn(0, 200);
  // Check if the robot is on the line
  if (sensorValue1 < threshold && sensorValue2 < threshold && sensorValue3 < threshold && sensorValue4 < threshold && sensorValue5 < threshold) {
    // Stop the robot
    hardturnleft(255, 100); //turn left slightly
  } else {
    // Calculate the position of the robot on the line

    int position = 0;

    if (sensorValue3 < threshold) {
      position = 3;
    }
    if (sensorValue4 < threshold) {
      position = 4;
    }
    if (sensorValue5 < threshold) {
      position = 5;
    }
    if (sensorValue2 < threshold) {
      position = 2;
    }

    if (sensorValue1 < threshold) {
      position = 1;
    }
    if (sensorValue1 < threshold && sensorValue2 < threshold) {
      position = 6;
    }



    // Adjust the motor speed and direction based on the position
    if (position == 1) {
      // Turn left
      hardturnleft(255, 255);

    } else if (position == 2) {
      turn(255, 0);
    } else if (position == 3) {
      // Go straight
      forward(255);
    } else if (position == 4) {
      // Turn right slightly
      turn(0, 255);
    } else if (position == 5) {
      // Turn right
      hardturnright(255, 255);
    }
    else if (position == 6) {
      // forward?
      forward(150);
    }
  }
}

void A1_H1_V11() {

  int LDRValue = analogRead(LDR_Pin);

  if (LDRValue > 32) { //DETECTS THE LED
    while (LDRValue >= 28) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
      LDRValue = analogRead(LDR_Pin);
      left();
    }
    forward(0); //STOPS FOR 2500 ms
    LED++;
    if (LED == 2) {
      Serial.write('6');
    }
    delay(2500);
  }
  left();

}
void A1_H1_V12 () {

  int LDRValue = analogRead(LDR_Pin);

  if (LED < 2) {
    if (LDRValue > 42) {
      while (LDRValue > 30) {
        LDRValue = analogRead(LDR_Pin);
        left();
      }
      forward(0);
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }
  }
  if (LED >= 2) {
    if (LDRValue > 42) {
      while (LDRValue > 30) {
        LDRValue = analogRead(LDR_Pin);
        forward(200);
      }
      forward(0);
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }
  }

  if (LED == 2) {
    while (m == 0) {
      for (int pos = 0; pos <= 165; pos += 1) {
        turn(200, 150);
        delay(3);
      }
      m = 1;
    }
    V12();
  }
  else {
    left();
  }
}
void A2_H1_V11 () {

  int LDRValue = analogRead(LDR_Pin);
  if (LED < 2) {
    if (LDRValue > 35) { //DETECTS THE LED
      while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        right();
      }
      forward(0); //STOPS FOR 2500 ms
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }


    right(); //FOLLOWING LINE
  }
  if (LED >= 2) {

    if (LDRValue > 35) { //DETECTS THE LED
      while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        left();
      }
      forward(0); //STOPS FOR 2500 ms
      delay(2500);
    }
    left();

  }
}
void A2_H1_V12 () {

  int LDRValue = analogRead(LDR_Pin);
  if (LED < 2) {
    if (LDRValue > 35) { //DETECTS THE LED
      while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        right();
      }
      forward(0); //STOPS FOR 2500 ms
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }


    right(); //FOLLOWING LINE
  }
  if (LED >= 2) {
    if (m == 0) {
      unsigned long prev = millis();
      while (millis() - prev < 1000) {
        left();
      }
      m = 1;
    }
    V12();

    if (LDRValue > 35) { //DETECTS THE LED
      while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        left();
      }
      forward(0); //STOPS FOR 2500 ms
      delay(2500);
    }


  }
}
void A2_H2_V21() {


  int LDRValue = analogRead(LDR_Pin);

  if (LDRValue > 35) { //DETECTS THE LED
    while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
      LDRValue = analogRead(LDR_Pin);
      forward(255);
    }
    forward(0); //STOPS FOR 2500 ms
    LED++;
    if (LED == 2) {
      Serial.write('6');
    }
    delay(2500);
  }
  right(); //FOLLOWING LINE
}
void A2_H2_V22 () {
  int LDRValue = analogRead(LDR_Pin);

  if (LDRValue > 42) {
    while (LDRValue > 30) {
      LDRValue = analogRead(LDR_Pin);
      right();

    }
    forward(0);
    LED++;
    if (LED == 2) {
      Serial.write('6');
    }
    delay(2500);

  }
  if (LED == 2) {
    if (m == 0) {
      unsigned long prev = millis();
      while (millis() - prev < 1000) {
        right();
      }
      m = 1;
    }

    else V22();
  }
  else {
    right();
  }
}
void A1_H2_V21 () {


  int LDRValue = analogRead(LDR_Pin);
  if (LED < 2) {
    if (LDRValue > 32) { //DETECTS THE LED
      while (LDRValue >= 28) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        left();
      }
      forward(0); //STOPS FOR 2500 ms
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }
    left();
  }
  if (LED >= 2) {

    int LDRValue = analogRead(LDR_Pin);

    if (LDRValue > 35) { //DETECTS THE LED
      while (LDRValue >= 30) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        forward(255);
      }
      forward(0); //STOPS FOR 2500 ms
      delay(2500);
    }
    right(); //FOLLOWING LINE
  }
}

void A1_H2_V22 () {

  int LDRValue = analogRead(LDR_Pin);
  if (LED < 2) {
    if (LDRValue > 33) { //DETECTS THE LED
      while (LDRValue >= 28) { //ENTER A WHILE LOOP UNTIL THE IF CONDITION ISNT TRUE SO WHEN IT STOPS DONT STUCK
        LDRValue = analogRead(LDR_Pin);
        left();
      }
      forward(0); //STOPS FOR 2500 ms
      LED++;
      if (LED == 2) {
        Serial.write('6');
      }
      delay(2500);

    }


    left(); //FOLLOWING LINE
  }
  if (LED >= 2) {
    if (LDRValue > 42) {
      while (LDRValue > 30) {
        LDRValue = analogRead(LDR_Pin);
        right();
      }
      forward(0);
      delay(2500);
      LED++;
    }
    if (m == 0) {
      unsigned long prev = millis();
      while (millis() - prev < 1000) {
        right();
      }
      m = 1;
    }
    else V22();


  }
}


void loop() {

  while (response == "A1_H1_V11") {
    A1_H1_V11();
  }
  while (response == "A1_H1_V12") {
    A1_H1_V12();
  }
  while (response == "A2_H1_V11") {
    A2_H1_V11();
  }
  while (response == "A2_H1_V12") {
    A2_H1_V12();
  }

  while (response == "A2_H2_V21") {
    A2_H2_V21();
  }
  while (response == "A2_H2_V22") {
    A2_H2_V22();
  }
  while (response == "A1_H2_V21") {
    A1_H2_V21();
  }
  while (response == "A1_H2_V22") {
    A1_H2_V22();
  }
}
