#include <TimerOne.h>
const int stepPin1 = 11;
const int dirPin1 = 35;

const int stepPin2 = 5;  //
const int dirPin2 = 37;

const int stepPin3 = 6;  //
const int dirPin3 = 39;

const int stepPin4 = 44;  //
const int dirPin4 = 41;
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
  // delay(200);

  // digitalWrite(dirPin4, LOW);
  // for (int x = 0; x < 400; x++) {
  //   digitalWrite(stepPin4, HIGH);
  //   delayMicroseconds(500);
  //   digitalWrite(stepPin4, LOW);
  //   delayMicroseconds(500);
  // }

  // delay(1000);
}
//*/