#pragma once
#include <TimerOne.h>
#include <TimerFour.h>
#include <TimerThree.h>
#define MOTOR1_DIR_PIN 37
#define MOTOR1_STEP_PIN 5

#define MOTOR2_DIR_PIN 39
#define MOTOR2_STEP_PIN 6

#define DIST_PER_TICK_X 0.3
#define STEP_RESOLUTION 1

double V = 10000.0;  //max speed
int dir_xl = 1;
int dir_xr = 1;
void ISR_XL();
void ISR_XR();
int32_t tickL = 0, tickR = 0;  //накопление тиков
int32_t mDist = 0;
void motorSpd(double);

bool step_state_xl = 0, step_state_xr = 0;
int xl_curr = 0, xr_curr = 0;

void motor(int32_t dist) {
  mDist += dist;
  int32_t d = ((dist / (30 * M_PI)) * 200) * 32.0;
  while (tickL < d) {
    motorSpd(1000.0);
    // Serial.println(String(tickL) + "  " + String(tickR));
    motorSpd(500.0);
  }
  motorSpd(0.0);
}


void motorSpd(double speed_xl) {
  double speed_xr = speed_xl;
  speed_xl = speed_xl * -1;
  static double speed_xl_last, speed_xr_last;

  if (abs(speed_xl) > 1) {
    if (speed_xl > 0)
      dir_xl = 1;
    else dir_xl = -1;

    speed_xl = abs(speed_xl);
    speed_xl = constrain(speed_xl, 0, V);
    speed_xl = 1000000 * DIST_PER_TICK_X / speed_xl / 2 / STEP_RESOLUTION;

    if (speed_xl_last != speed_xl) {
      Timer1.setPeriod(speed_xl);
      Timer1.start();
    }
    speed_xl_last = speed_xl;

    // in_home = false;
  } else {
    Timer1.stop();
  }
  //-------------------------------------------------------------
  if (abs(speed_xr) > 1) {
    if (speed_xr > 0) dir_xr = -1;
    else dir_xr = 1;

    speed_xr = abs(speed_xr);
    speed_xr = constrain(speed_xr, 0, V);
    speed_xr = 1000000 * DIST_PER_TICK_X / speed_xr / 2 / STEP_RESOLUTION;

    if (speed_xr_last != speed_xr) {
      Timer4.setPeriod(speed_xr);
      Timer4.start();
    }
    speed_xr_last = speed_xr;

    // in_home = false;
  } else {
    Timer4.stop();
  }
}

void init_motors() {
  // Настройка пинов
  pinMode(MOTOR1_DIR_PIN, OUTPUT);
  pinMode(MOTOR1_STEP_PIN, OUTPUT);
  pinMode(MOTOR2_DIR_PIN, OUTPUT);
  pinMode(MOTOR2_STEP_PIN, OUTPUT);

  // Инициализация Timer1
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_XL);
  Timer1.stop();

  Timer4.initialize(1000);
  Timer4.attachInterrupt(ISR_XR);
  Timer4.stop();
}

void ISR_XL() {
  digitalWrite(MOTOR1_STEP_PIN, step_state_xl);
  digitalWrite(MOTOR1_DIR_PIN, dir_xl == 1 ? 1 : 0);
  tickL += dir_xl * step_state_xl;

  xl_curr += (dir_xl * step_state_xl * DIST_PER_TICK_X / STEP_RESOLUTION);

  step_state_xl = 1 - step_state_xl;
}

void ISR_XR() {
  digitalWrite(MOTOR2_STEP_PIN, step_state_xr);
  digitalWrite(MOTOR2_DIR_PIN, dir_xr == 1 ? 1 : 0);

  tickR += dir_xr * step_state_xr;

  xr_curr += (dir_xr * step_state_xr * DIST_PER_TICK_X / STEP_RESOLUTION);

  step_state_xr = 1 - step_state_xr;
}