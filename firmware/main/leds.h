#pragma once
//вкладка для работы со светодиодами

void _initLeds() {
  pinMode(31, OUTPUT);
}

void on() {
  digitalWrite(31, HIGH);
}
void off() {
  digitalWrite(31, LOW);
}