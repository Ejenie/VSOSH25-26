#include "timers.h"
#include "motors.h"
#include "imu.h"
#include "odom.h"

float wall(float mL = 90, float mR = 90, float kp = 1.2) {
  float err = (584 - analogRead(A2));
  float u = err * kp;
  return u;
}