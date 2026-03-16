#include "drivers.h"  //разбиение крда для более удобной работы
#include "servos.h"
#include "serials.h"
#include "leds.h"
#include "lightSensors.h"
#include "conditions.h"
#include "butt.h"

int32_t rightR[2] = { -1, -1 };  //массив направлений моторов рейки, дающих езду вправо
int32_t leftR[2] = { 1, 1 };     //массив направлений моторов рейки, дающих езду влево

int32_t upP[2] = { 1, -1 };      //массив направлений моторов плоттера, дающих езду вверх
int32_t downP[2] = { -1, -1 };  //массив направлений моторов плоттера, дающих езду вниз
int32_t rightP[2] = {1, 1 };  //массив направлений моторов плоттера, дающих езду вправо
int32_t leftP[2] = { 1, 1 };   //массив направлений моторов плоттера, дающих езду влево

void setup() {
  //инициализация перифирийных устройств
  _initSerials();
  _initMotorsLib();
  _initServos();
  _initLeds();
  _initButt();

  //код для выполнения тестового задания
  upServo();
  waitWhite();
  on();
  
  //gotoPosRail(rightR, 3600);
  //downServo();
  gotoPosPlotter(rightP, 2300);
  //gotoPosPlotter(downP, 2300);
  //upServo();
  //gotoPosRail(leftR, 3600);*/
}
void loop() {
  //_readLine();
  //Serial.println(String(analogRead(A4)) + " " + String(analogRead(A5)));
  planner.tick();
}
