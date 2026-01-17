void setup() {
  //инициализация
  _initMotors();
  _initServo();
  _initButtons();
  _initLightSens();
  _initSwitches();

  calibrMotors();
  calibrPen();
}
void loop() {
  updateCondition();
  switch(condition) {
    case 1:
      goToWorkspace();
    case 2:
      
  }
}
