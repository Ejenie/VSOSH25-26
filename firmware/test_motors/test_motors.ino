#include "drivers.h"
#include "servos.h"

void setup() {
  //инициализация
  _initMotorsLib();
  _initServos();

  down();

  //setPosAll(4200, 2400, false, true);
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
