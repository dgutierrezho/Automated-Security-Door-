#include <Modulino.h>
ModulinoBuzzer buzzer;

// ---- Pins ----
const int buttonPins[4] = {2, 3, 4, 5};
const int ledPins[4]    = {14, 15, 16, 17};
const int redLedPin     = 8;
const int greenLedPin   = 9;
const int SERVO_PIN     = 6; // servo control pin

// ---- Servo timing constants ----
const int FRAME_US  = 20000; // 20 ms = 50 Hz
const int MIN_US    = 300;   // pulse for "0°"
const int MAX_US    = 1700;  // pulse for "180°"
const int MOVE_ANGLE = 180;  // degrees to move forward/back
const int STEPS      = 40;   // smooth steps
const int DURATION_MS = 500; // time to move forward/back
const unsigned long HOLD_TIME = 3000; // wait at end

int currentAngle = 0; // logical current angle

// ---- Password ----
const int code[4] = {1, 2, 3, 4};
int entered[4] = {0, 0, 0, 0};
int indexPos = 0;

// ---- Timing ----
const unsigned long TIME_LIMIT = 5000;
unsigned long startTime = 0;
bool timerRunning = false;

void setup() {
  Serial.begin(9600);

  Modulino.begin();
  buzzer.begin();

  pinMode(SERVO_PIN, OUTPUT);
  digitalWrite(SERVO_PIN, LOW);

  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  if (timerRunning && (millis() - startTime > TIME_LIMIT)) {
    timeoutFail();
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      handlePress(i + 1);
      delay(250);
      break;
    }
  }
}

void handlePress(int buttonNumber) {
  if (!timerRunning) {
    startTime = millis();
    timerRunning = true;
  }

  if (indexPos >= 4) return;

  digitalWrite(ledPins[buttonNumber - 1], HIGH);
  entered[indexPos++] = buttonNumber;

  if (indexPos == 4) compareCode();
}

void compareCode() {
  bool correct = true;
  for (int i = 0; i < 4; i++) {
    if (entered[i] != code[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    digitalWrite(greenLedPin, HIGH);
    soundCorrect();
    openDoorOnce(MOVE_ANGLE, DURATION_MS, HOLD_TIME);
    digitalWrite(greenLedPin, LOW);
  } else {
    digitalWrite(redLedPin, HIGH);
    soundWrong();
    digitalWrite(redLedPin, LOW);
  }

  resetEntry();
}

void timeoutFail() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(redLedPin, HIGH);
    soundTimeout();
    delay(300);
    digitalWrite(redLedPin, LOW);
    delay(300);
  }
  resetEntry();
}

void resetEntry() {
  for (int i = 0; i < 4; i++) {
    entered[i] = 0;
    digitalWrite(ledPins[i], LOW);
  }
  indexPos = 0;
  timerRunning = false;
}

// ---------- Sounds ----------
void soundCorrect() {
  buzzer.tone(400, 500);
  delay(550);

  int midNotes[] = {600, 800, 1000};
  for (int i = 0; i < 3; i++) {
    buzzer.tone(midNotes[i], 150);
    delay(200);
  }

  delay(200);

  int highNotes[] = {1200, 1400, 1600};
  int highDur[]   = {100, 100, 200};
  for (int i = 0; i < 3; i++) {
    buzzer.tone(highNotes[i], highDur[i]);
    delay(highDur[i] + 50);
  }
}

void soundWrong() {
  buzzer.tone(1000, 150);
  delay(200);
  buzzer.tone(300, 400);
  delay(450);
}

void soundTimeout() {
  buzzer.tone(500, 100);
  delay(150);
}

// ---------- Servo helpers ----------
int angleToPulseUs(int angle) {
  angle = constrain(angle, 0, 180);
  return map(angle, 0, 180, MIN_US, MAX_US);
}

void sendServoPulseUs(int pulseUs) {
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(pulseUs);
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(FRAME_US - pulseUs);
}

// ---------- New barebones servo motion ----------
void openDoorOnce(int moveAngle, int durationMs, unsigned long holdMs) {
  // --- Move forward ---
  for (int a = 0; a <= moveAngle; a += moveAngle / STEPS) {
    sendServoPulseUs(angleToPulseUs(currentAngle + a));
    delay(durationMs / STEPS);
  }
  currentAngle += moveAngle;

  // --- Hold at max ---
  delay(holdMs);

  // --- Move back ---
  for (int a = 0; a <= moveAngle; a += moveAngle / STEPS) {
    sendServoPulseUs(angleToPulseUs(currentAngle - a));
    delay(durationMs / STEPS);
  }
  currentAngle -= moveAngle;

  // --- Hold at start ---
  delay(holdMs);
}
