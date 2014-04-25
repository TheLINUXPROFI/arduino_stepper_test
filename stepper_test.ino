const int stepPin = 13;    
const int dirPin =  12;    
const int stepsInFullRound = 400;

// Set pins
void setup() {
  pinMode(stepPin, OUTPUT);     
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW); 
}

void run(boolean runForward, double speedRPS, int stepCount) {
  digitalWrite(dirPin, runForward);
  for (int i = 0; i < stepCount; i++) {
    digitalWrite(stepPin, HIGH);
    holdHalfCylce(speedRPS);
    digitalWrite(stepPin, LOW);
    holdHalfCylce(speedRPS);
  }
}

void holdHalfCylce(double speedRPS) {
  long holdTime_us = (long)(1.0 / (double) stepsInFullRound / speedRPS / 2.0 * 1E6);
  int overflowCount = holdTime_us / 65535;
  for (int i = 0; i < overflowCount; i++) {
    delayMicroseconds(65535);
  }
  delayMicroseconds((unsigned int) holdTime_us);
}

// Runs the motor once in forward direction and once to the opposite direction.
// Holds the motor still for 1 sec after both movements.
void runBackAndForth(double speedRPS, int rounds) {
  run(true, speedRPS, stepsInFullRound * rounds);
  delay(1000);
  run(false, speedRPS, stepsInFullRound * rounds);
  delay(1000);
}

// Tests various speeds for 10 full rotations
void loop(){
  runBackAndForth(1, 10);
  runBackAndForth(5, 10);
  runBackAndForth(7, 10);
}
