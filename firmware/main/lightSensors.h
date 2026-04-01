#pragma once
//вкладка для работы с датчиками  линии

void _initLightSensors() {
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
  pinMode(29, INPUT);
}

void _readLine() {
  Serial.println(String(analogRead(A6)) + " " + String(analogRead(A7)) + " " + 
  String(analogRead(A8)) + " " + String(analogRead(A9)) + " " + 
  String(analogRead(A10)) + " " + String(analogRead(A11)) + " " + 
  String(analogRead(A12)) + " " + String(analogRead(A13)));
}