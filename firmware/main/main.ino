#include "display.h"  //разбиение крда для более удобной работы
#include "serials.h"
#include "leds.h"
#include "lightSensors.h"
#include "butt.h"
#include "drivers.h"
#include "servos.h"
#include "conditions.h"

void setup() {
  //инициализация перифирийных устройств
  _initSerials();
  _initDisplay();
  _initMotorsLib();
  _initServos();
  _initLeds();
  _initButt();

  //код для выполнения тестового задания
  upServo();
  while (!waitGreen()) {
    beginCond();
  }
  on();
  //gotoPosPlotter(downP, 2300);
  //upServo();
  //gotoPosRail(leftR, 3600);*/
}
void loop() {
  switch (condition) {
    case 2:
      test();
  }
  reset();
  //planner.tick();
}
