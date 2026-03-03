float cur_vel_left = 0;
float cur_vel_right = 0;

float speed_controllerL(float target_vel, float cur_enc) {
  static float km = 11.0, Tm = 0.04, Tmu = time_loop / 1000000.0, usk = Tm / 2.0 / Tmu;
  static float kp = usk / km, ki = usk / (km * Tm);

  static float old_angle = 0;
  float delta_angle = cur_enc - old_angle;

  float delta_time = time_loop / 1000000.0;

  float cur_vel = delta_angle / delta_time;
  cur_vel_left = cur_vel;
  old_angle = cur_enc;

  float err = (target_vel - cur_vel), p = err * kp;
  float u = p;

  return u;
}


float speed_controllerR(float target_vel, float cur_enc) {
  static float km = 11.0, Tm = 0.04, Tmu = time_loop / 1000000.0, usk = Tm / 2.0 / Tmu;
  static float kp = usk / km, ki = usk / (km * Tm);

  static float old_angle = 0;
  float delta_angle = cur_enc - old_angle;

  float delta_time = time_loop / 1000000.0;

  float cur_vel = delta_angle / delta_time;
  cur_vel_right = cur_vel;
  old_angle = cur_enc;

  float err = (target_vel - cur_vel), p = err * kp;
  float u = p;
}
