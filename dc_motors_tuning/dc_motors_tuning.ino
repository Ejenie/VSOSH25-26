#include "other.h"

void setup() {
  Serial.begin(115200);
  _initMotors();
  _initEnc();

}

void loop() {
  //T
  smart_timer(time_loop);

  //S
  float cur_encL = encL, cur_encR = encR;
  float uL = speed_controllerL(1100, cur_encL);
        //uR = speed_controllerR(200, cur_encR);

  //P


  //A
  motors(uL, 0);
  //Serial.println(String(cur_encL) + " " + String(cur_encR));
}
