const int stepPin1 = 35;
const int dirPin1 = 36;
const int stepPin2 = 37;
const int dirPin2 = 38;
const int stepPin3 = 39;
const int dirPin3 = 40;
const int stepPin4 = 41;
const int dirPin4 = 42;

void _initMotors() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
}

void move1() {
  digitalWrite(dirPin1, HIGH);
  for (int x = 0; x < 200; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  delay(200);

  digitalWrite(dirPin1, LOW);
  for (int x = 0; x < 400; x++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }

  delay(1000);
}


void move2() {
  digitalWrite(dirPin2, HIGH);
  for (int x = 0; x < 200; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(200);

  digitalWrite(dirPin2, LOW);
  for (int x = 0; x < 400; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }

  delay(1000);
}
