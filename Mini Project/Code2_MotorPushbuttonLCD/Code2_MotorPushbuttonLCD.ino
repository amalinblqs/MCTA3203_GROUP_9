#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change address if needed

// Button Pins
const int powerButton = 3;
const int modeButton = 4;
const int startButton = 5;

// Motor Control Pins (L9110S)
const int motorPin1 = 6;
const int motorPin2 = 7;

// Wash Programs
enum WashMode { COTTON, SYNTHETIC, DELICATE, QUICK };
WashMode currentMode = COTTON;
const char* modeNames[] = { "COTTON", "SYNTHETIC", "DELICATE", "QUICK" };

// Machine States
enum MachineState { OFF, STANDBY, RUNNING, PAUSED, COMPLETE };
MachineState state = OFF;

// Cycle Phases
enum CyclePhase { WASH, RINSE, SPIN, DONE };
CyclePhase currentPhase = WASH;

// Timing
unsigned long washTimes[] = { 45, 30, 20, 1 }; // In minutes
unsigned long totalTime = 0;
unsigned long phaseStartTime = 0;
unsigned long currentPhaseDuration = 0;
unsigned long startTime = 0;

void setup() {
  pinMode(powerButton, INPUT_PULLUP);
  pinMode(modeButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  lcd.init();
  lcd.backlight();
  updateDisplay();
}

void loop() {
  checkButtons();
  updatePhaseAndTimer();
  controlMotor();
  updateDisplay();
  delay(100);
}

void checkButtons() {
  if (digitalRead(powerButton) == LOW) {
    if (state == OFF) state = STANDBY;
    else state = OFF;
    delay(300);
  }

  if (state != OFF && digitalRead(modeButton) == LOW) {
    currentMode = (WashMode)((currentMode + 1) % 4);
    delay(300);
  }

  if (state == STANDBY && digitalRead(startButton) == LOW) {
    state = RUNNING;
    currentPhase = WASH;
    totalTime = washTimes[currentMode] * 60000UL;
    phaseStartTime = millis();
    startTime = millis();
  } 
  else if (state == RUNNING && digitalRead(startButton) == LOW) {
    state = PAUSED;
    delay(300);
  } 
  else if (state == PAUSED && digitalRead(startButton) == LOW) {
    state = RUNNING;
    phaseStartTime = millis(); // resumes from beginning of paused phase
    delay(300);
  }
}

void updatePhaseAndTimer() {
  if (state != RUNNING) return;

  unsigned long elapsed = millis() - startTime;

  if (elapsed < totalTime * 0.5) {
    currentPhase = WASH;
    currentPhaseDuration = totalTime * 0.5;
  } else if (elapsed < totalTime * 0.8) {
    currentPhase = RINSE;
    currentPhaseDuration = totalTime * 0.3;
  } else if (elapsed < totalTime) {
    currentPhase = SPIN;
    currentPhaseDuration = totalTime * 0.2;
  } else {
    currentPhase = DONE;
    state = COMPLETE;
  }
}

void updateDisplay() {
  lcd.clear();
  switch (state) {
    case OFF:
      lcd.print("WASHING MACHINE");
      lcd.setCursor(0, 1);
      lcd.print("PRESS POWER");
      break;
    case STANDBY:
      lcd.print("MODE: ");
      lcd.print(modeNames[currentMode]);
      lcd.setCursor(0, 1);
      lcd.print("TIME: ");
      lcd.print(washTimes[currentMode]);
      lcd.print(" min");
      break;
    case RUNNING:
    case PAUSED:
      lcd.print(modeNames[currentMode]);
      lcd.print(" ");
      lcd.print(state == PAUSED ? "PAUSED" : "RUNNING");
      lcd.setCursor(0, 1);
      lcd.print("PHASE: ");
      lcd.print(getPhaseName(currentPhase));
      break;
    case COMPLETE:
      lcd.print("CYCLE COMPLETE!");
      lcd.setCursor(0, 1);
      lcd.print("PRESS POWER");
      break;
  }
}

// ------------------------------
// Motor Control Logic
// ------------------------------
void controlMotor() {
  if (state == RUNNING && (currentPhase == WASH || currentPhase == SPIN)) {
    motorForward();
  } else {
    stopMotor();
  }
}

void motorForward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void motorReverse() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void stopMotor() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

// ------------------------------
// Utility
// ------------------------------
const char* getPhaseName(CyclePhase phase) {
  switch (phase) {
    case WASH: return "WASH";
    case RINSE: return "RINSE";
    case SPIN: return "SPIN";
    case DONE: return "DONE";
    default: return "";
  }
}