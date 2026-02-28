volatile int16_t encL = 0, encR = 0;

void encoderL() {
  if (digitalRead(14)) encL++; else encL--;
}
void encoderR(){
  if (digitalRead(15)) encR++; else encR--;
}

void _initMotors() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
}

void _initEnc() {
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  attachInterrupt(0, encoderL, 3);
  attachInterrupt(1, encoderR, 3);
}