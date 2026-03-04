#include "motors.h"
#include "imu.h"

void reg(int mL = 120, int mR = 120, float kp = 5.0) {
  float err = 0 - deltaIMU; float u = err * kp;
  motors(mL - u, mR + u);
}