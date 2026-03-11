#include "st.h"
#include <GyverStepper2.h>
#include <GyverPlanner2.h>

GStepper2<STEPPER2WIRE> railOne(1, 5, 37);
GStepper2<STEPPER2WIRE> railTwo(1, 11, 35);

GStepper2<STEPPER2WIRE> plotterOne(1, 6, 39);
GStepper2<STEPPER2WIRE> plotterTwo(1, 44, 41);

GPlanner2<STEPPER2WIRE, 4> planner;

void queueTarget(int32_t railOne, int32_t railTwo, int32_t plotterOne, int32_t plotterTwo) {
  int32_t cur[4] = { planner.getCurrent(0), planner.getCurrent(1),
                     planner.getCurrent(2), planner.getCurrent(3) };

  // if (speed < 1) speed = 1;
  // if (accel < 1) accel = 1;

  int32_t tar[4] = { railOne, railTwo,
                     plotterOne, plotterTwo };
  planner.stop();
  planner.clearBuffer();
  planner.addTarget(cur, 0);
  planner.addTarget(tar,1);
  planner.start();
}

void setPosRail(float Mm) {
  int32_t railOne = Mm * 1.6 * -1.0;
  int32_t railTwo = Mm * 1.6 * -1.0;
  int32_t plotterOne = planner.getCurrent(2);
  int32_t plotterTwo = planner.getCurrent(3);
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

void setPosPlotter(float Mm) {
  int32_t railOne = planner.getCurrent(0);
  int32_t railTwo = planner.getCurrent(1);
  int32_t plotterOne = Mm * 0.1 * -1.0;
  int32_t plotterTwo = Mm * 0.1 * -1.0;
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

void setup() {
  //инициализация
  //_initMotors();
  /* _initServo();
  _initButtons();
  _initLightSens();
  _initSwitches();

  calibrMotors();
  calibrPen();*/

  planner.addStepper(0, railOne);
  planner.addStepper(1, railTwo);
  planner.addStepper(2, plotterOne);
  planner.addStepper(3, plotterTwo);
  planner.setMaxSpeed(1000);
  planner.setAcceleration(550);
  setPosRail(425);  //*/
   setPosPlotter(100);
}
void loop() {
  planner.tick();
  //move1();
  //motorSpd(100.0);
  /*updateCondition();
  switch(condition) {
    case 1:
      goToWorkspace();
    case 2:
      
  }*/
  //move1();
}
