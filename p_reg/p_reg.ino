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
  //T
  smart_timer(time_loop);

  //S
  float cur_encL = encL, cur_encR = encR;
  float uL = speed_controllerL(110, cur_encL), uR = speed_controllerR(110, cur_encR);
  //float uWall = wall();

  //P
  //odom_tick();

  //A
  //motors(uL, uR);
  //Serial.println(odom_get_S());
  _checkIMU();
  //Serial.println(String(cur_encL) + " " + String(cur_encR));
}
