#pragma once
//вкладка для работы с сервомотором
#include <Servo.h>
Servo marker;

void _initServos() {
  marker.attach(A0);
}

void upServo() {
  marker.write(100);
}

void downServo() {
  marker.write(0);
}