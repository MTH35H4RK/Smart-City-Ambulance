int buzzerPin = 2;
int redLedPin = 11;
int blueLedPin = 13;
int sirenState = 0;

unsigned long lastSirenChangeTime = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Change siren state every 400 milliseconds
  if (currentMillis - lastSirenChangeTime >= 400) {
    lastSirenChangeTime = currentMillis;
    sirenState = 1 - sirenState;
    
    // Play tone based on siren state
    if (sirenState == 1) {
      tone(buzzerPin, 1450);
      digitalWrite(redLedPin, HIGH);
      digitalWrite(blueLedPin, LOW);
    } else {
      tone(buzzerPin, 550);
      digitalWrite(redLedPin, LOW);
      digitalWrite(blueLedPin, HIGH);
    }
  }
}
