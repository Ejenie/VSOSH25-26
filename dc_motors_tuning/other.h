#include "timers.h"
#include "motors.h"

float speed_controllerL(float target_vel, float cur_enc) {
  static float km = 11.0, Tm = 0.04, Tmu = time_loop / 1000000.0, usk = Tm / 2.0 / Tmu;
  static float kp = usk / km, ki = usk / (km * Tm);

  static float old_angle = 0;
  float delta_angle = cur_enc - old_angle;

  float delta_time = time_loop / 1000000.0;

  float cur_vel = delta_angle / delta_time;
  old_angle = cur_enc;

  float err = (target_vel - cur_vel), p = err * kp;
  float u = p;
  
  /*static float I = 0;
  const float i = I * ki;
  const float u = p + i;
  if (u == constrain(u, -255.0, 255.0))
    I += err * time_loop / 1000000.0;*/

  Serial.println("leftu " + String(u) + " err " + String(err) + " vel " + String(cur_vel));

  return u;
}


float speed_controllerR(float target_vel, float cur_enc) {
  static float old_angle = 0;
  float delta_angle = cur_enc - old_angle;

  float delta_time = time_loop / 1000000.0;

  float cur_vel = delta_angle / delta_time;
  old_angle = cur_enc;

  //Serial.print("\tright " + String(cur_vel / target_vel));

  return 0;
}
