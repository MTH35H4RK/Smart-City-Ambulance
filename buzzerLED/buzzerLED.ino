int buzzerPin = 8;
int redLedPin = 9;
int blueLedPin = 10;

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
      tone(buzzerPin, 880);
      digitalWrite(redLedPin, HIGH);
      digitalWrite(blueLedPin, LOW);
    } else {
      tone(buzzerPin, 660);
      digitalWrite(redLedPin, LOW);
      digitalWrite(blueLedPin, HIGH);
    }
  }
}
