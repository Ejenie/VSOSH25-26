#include "other.h"

void setup() {
  Serial.begin(115200);
  _initMotors();
  _initEnc();

}

void loop() {
  //T
  smart_timer(5000);

  //S
  float cur_encL = encL, cur_encR = encR;
  float uL = -110, uR = -110;

  //P


  //A
  motors(uL, uR);
  Serial.println(String(cur_encL) + " " + String(cur_encR));
}
