#include "speed.h"
#define ROBOT_WHEEL_RADIUS 0.035
#define ROBOT_WIDTH 0.1

float odom_S = 0.0;
float odom_theta = 0.0;

void odom_reset() {
  odom_S = 0;
  odom_theta = 0;
}

void odom_tick() {
  float w_l = cur_vel_left;
  float w_r = cur_vel_right;

  float v_l = w_l * ROBOT_WHEEL_RADIUS;
  float v_r = w_r * ROBOT_WHEEL_RADIUS;

  float v = (v_l + v_r) / 2;
  float theta_i = (v_r - v_l) / ROBOT_WIDTH;

  odom_S += v * time_loop / 1000000.0;
  odom_theta += theta_i * time_loop / 1000000.0;
}

float odom_get_S() {
  return odom_S;
}

float odom_get_theta() {
  return odom_theta;
}
