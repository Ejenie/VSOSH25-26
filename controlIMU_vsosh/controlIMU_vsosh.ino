#include "other.h"

void setup() {
  Serial.begin(115200);
  _initMotors();
  _initEnc();
  _initIMU();
  pinMode(13, INPUT_PULLUP);
  zeroIMU();
}

void loop() {
  //_checkIMU(dataIMUreal);
  updateIMU(dataIMUreal);
  updateDelta();
  Serial.println(String(dataIMUreal[0]) + " " + String(dataIMU) + " " + String(deltaIMU));
  if (!digitalRead(13)){
    zeroIMU();
  }
}
