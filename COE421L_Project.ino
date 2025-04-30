const int ledPins[4] = {2, 3, 4, 5};       // LEDs on pins 2-5
const int sensorPins[4] = {A0, A1, A2, A3}; // Light sensors on A0-A3
const int buzzerPin = 7;                    // Buzzer on pin 7
const int buttonPin = 6;                    // Start button on pin 6
const int SENSOR_THRESHOLD = 20;            // Covered = <20, Uncovered = >20

int currentRound = 1;
String sequence = "";
bool gameActive = false;

void setup() {
  Serial.begin(9600); // USB Serial
  for(int i=0; i<4; i++) pinMode(ledPins[i], OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  randomSeed(analogRead(A5));
  Serial.println("SYSTEM_READY");
}

void loop() {
  if(!gameActive) {
    waitForStartButton();
    startCountdown();  // 3-second countdown with buzzer
    gameActive = true;
    currentRound = 1;
    Serial.println("ROUND:" + String(currentRound));
  }

  if(gameActive) {
    sequence = generateSequence(currentRound);
    playSequence();
    bool success = validatePlayerInput();

    if(success) {
      currentRound++;
      Serial.println("ROUND:" + String(currentRound));
      delay(1000);
    } else {
      gameOver();
      gameActive = false;
    }
  }
}

// New countdown function
void startCountdown() {
  for(int i = 3; i > 0; i--) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("COUNTDOWN:" + String(i));
    delay(500);  // 0.5 second buzzer on
    digitalWrite(buzzerPin, LOW);
    delay(500);  // 0.5 second buzzer off
  }
}

String generateSequence(int length) {
  String seq = "";
  for(int i=0; i<length; i++) seq += String(random(0,4));
  return seq;
}

void playSequence() {
  for(int i=0; i<sequence.length(); i++) {
    int led = sequence.charAt(i) - '0';
    digitalWrite(ledPins[led], HIGH);
    delay(500);
    digitalWrite(ledPins[led], LOW);
    delay(300);
  }
}

bool validatePlayerInput() {
  for(int step=0; step<sequence.length(); step++) {
    int expectedSensor = sequence.charAt(step) - '0';
    bool correct = false;
    unsigned long start = millis();

    while(millis()-start < 10000 && !correct) {
      for(int sensor=0; sensor<4; sensor++) {
        if(analogRead(sensorPins[sensor]) < SENSOR_THRESHOLD) {
          Serial.println("PRESSED:" + String(sensor));
          digitalWrite(ledPins[sensor], HIGH);
          delay(200);
          
          if(sensor == expectedSensor) {
            correct = true;
          } else {
            digitalWrite(ledPins[sensor], LOW);
            return false;
          }
          
          digitalWrite(ledPins[sensor], LOW);
          delay(300);
          break;
        }
      }
    }
    if(!correct) return false;
  }
  return true;
}

void gameOver() {
  Serial.println("GAME_OVER");
  for(int i=0; i<3; i++) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }
}

void waitForStartButton() {
  while(digitalRead(buttonPin) == HIGH); // Wait for button press (LOW)
  delay(300); // Debounce
}
