#pragma once
#include <GyverStepper2.h>  //объявление управляющих библиотек
#include <GyverPlanner2.h>

#define maxSpeed 2800  //объявление максимальной скорости, с которой могут работать шаговики
#define acc 1500       //объявление максимального ускорения, с которым могут работать шаговики

#define constRail 20.4   //константа для пересчета шагов двигателя в миллиметры для езды по рейке
#define constPlotter 20  //константа для пересчета шагов двигателя в миллиметры для езды внетри плоттера

//объявление экземпляров классса для работы с шаговиками
GStepper2<STEPPER2WIRE> railOne(1, 5, 37);
GStepper2<STEPPER2WIRE> railTwo(1, 11, 35);

GStepper2<STEPPER2WIRE> plotterOne(1, 6, 39);
GStepper2<STEPPER2WIRE> plotterTwo(1, 44, 41);

GPlanner2<STEPPER2WIRE, 4> planner;

int32_t rightR[2] = { -1, -1 };  //массив направлений моторов рейки, дающих езду вправо
int32_t leftR[2] = { 1, 1 };    //массив направлений моторов рейки, дающих езду влево

int32_t upP[2] = { 1, -1 };     //массив направлений моторов плоттера, дающих езду вверх
int32_t downP[2] = { -1, -1 };  //массив направлений моторов плоттера, дающих езду вниз
int32_t rightP[2] = { -1, 1 };  //массив направлений моторов плоттера, дающих езду вправо
int32_t leftP[2] = { 1, -1 };   //массив направлений моторов плоттера, дающих езду влево

//ф-я задания цели работы шаговиков в относительной системе координат
void queueTarget(int32_t railOne, int32_t railTwo, int32_t plotterOne, int32_t plotterTwo) {
  int32_t cur[4] = { planner.getCurrent(0), planner.getCurrent(1),
                     planner.getCurrent(2), planner.getCurrent(3) };
  int32_t tar[4] = { railOne, railTwo,
                     plotterOne, plotterTwo };
  planner.stop();
  planner.clearBuffer();
  planner.addTarget(cur, 0, RELATIVE);
  planner.addTarget(tar, 1, RELATIVE);
  planner.start();
}

//ф-я подачи на моторы значений позиции в миллиметрах. выполняется параллельно с другими
void setPosAll(float mmRail, float mmPlotter, int32_t dirRail[2], int32_t dirPlotter[2]) {
  int signRail = dirRail[0];

  int signPlotterOne = dirPlotter[0];
  int singPlotterTwo = dirPlotter[1];

  int32_t railOne = mmRail * constRail * signRail;
  int32_t railTwo = mmRail * constRail * signRail;

  int32_t plotterOne = mmPlotter * constPlotter * signPlotterOne;
  int32_t plotterTwo = mmPlotter * constPlotter * singPlotterTwo;
  Serial.println(String(plotterOne) + " " + String(plotterTwo));
  queueTarget(railOne, railTwo, plotterOne, plotterTwo);
}

//ф-я подачи на моторы рейки значений позиции в миллиметрах. выполняется последовательно
void gotoPosRail(int32_t dir[2], float Mm) {
  setPosAll(Mm, 0, dir, dir);
  unsigned long start = millis();
  while (planner.tick() || (millis() - start < 1000)) {
  }
}

//ф-я подачи на моторы плоттера значений позиции в миллиметрах. выполняется последовательно
void gotoPosPlotter(int32_t dir[2], float Mm) {
  setPosAll(0, Mm, dir, dir);
  unsigned long start = millis();
  while (planner.tick() || (millis() - start < 1000)) {
  }
}

void _initMotorsLib() {
  planner.addStepper(0, railOne);
  planner.addStepper(1, railTwo);
  planner.addStepper(2, plotterOne);
  planner.addStepper(3, plotterTwo);

  planner.setMaxSpeed(maxSpeed);
  planner.setAcceleration(acc);
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