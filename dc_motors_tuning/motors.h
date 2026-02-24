volatile int16_t encL = 0, encR = 0;

void encoderL() {
  if(digitalRead(14)) encL--; else encL++;
}

void encoderR() {
  if(digitalRead(15)) encR++; else encR--;
}

void _initEnc() {
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  attachInterrupt(0, encoderL, 3);
  attachInterrupt(1, encoderR, 3);
}

void _initMotors() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
}

void motors(int mL, int mR) {
  digitalWrite(4, mL < 0);
  mL = abs(mL);
  if (mL > 255) mL = 255;
  analogWrite(5, mL);

  digitalWrite(7, mR < 0);
  mR = abs(mR);
  if (mR > 255) mR = 255;
  analogWrite(6, mR);
}
