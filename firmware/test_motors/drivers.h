#pragma once
#include <GyverStepper2.h>
#include <GyverPlanner2.h>

#define maxSpeed 2800
#define acc 1500
#define constRail 1.6
#define constPlotter 5.0

GStepper2<STEPPER2WIRE> railOne(1, 5, 37);
GStepper2<STEPPER2WIRE> railTwo(1, 11, 35);

GStepper2<STEPPER2WIRE> plotterOne(1, 6, 39);
GStepper2<STEPPER2WIRE> plotterTwo(1, 44, 41);

GPlanner2<STEPPER2WIRE, 4> planner;

void queueTarget(int32_t railOne, int32_t railTwo, int32_t plotterOne, int32_t plotterTwo) {
  int32_t cur[4] = { planner.getCurrent(0), planner.getCurrent(1),
                     planner.getCurrent(2), planner.getCurrent(3) };
  int32_t tar[4] = { railOne, railTwo,
                     plotterOne, plotterTwo };
  planner.stop();
  planner.clearBuffer();
  planner.addTarget(cur, 0);
  planner.addTarget(tar, 1);
  planner.start();
}

void setPosAll(float mmRail, float mmPlotter, bool dirRail = false, bool dirPlotter = false) {
  int signRail = -1;
  if (dirRail) signRail = 1;
  
  int signPlotter = -1;
  if (dirPlotter) signPlotter = 1;

  int32_t railOne = mmRail * constRail * signRail;
  int32_t railTwo = mmRail * constRail * signRail;

  int32_t plotterOne = mmPlotter * constPlotter * signPlotter;
  int32_t plotterTwo = mmPlotter * constPlotter * signPlotter;
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

void setPosRail(float Mm) {
  int32_t railOne = Mm * constRail * -1.0;
  int32_t railTwo = Mm * constRail * -1.0;
  int32_t plotterOne = planner.getCurrent(2);
  int32_t plotterTwo = planner.getCurrent(3);  //*/
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

void setPosPlotter(float Mm) {
  int32_t railOne = planner.getCurrent(0);
  int32_t railTwo = planner.getCurrent(1);
  int32_t plotterOne = Mm * constPlotter * -1.0;
  int32_t plotterTwo = Mm * constPlotter * -1.0;
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

void _initMotorsLib() {
  planner.addStepper(0, railOne);
  planner.addStepper(1, railTwo);
  planner.addStepper(2, plotterOne);
  planner.addStepper(3, plotterTwo);

  planner.setMaxSpeed(maxSpeed);
  planner.setAcceleration(acc);
}