#include "other.h"

void setup() {
  Serial.begin(115200);
  _initMotors();
  _initEnc();
  _initIMU();
  zeroIMU();
}

void loop() {
  //_checkIMU(dataIMUreal);
  updateIMU(dataIMUreal);
  updateDelta();
  reg();
}
