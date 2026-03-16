#pragma once
//вкладка для работы с кнопками

void _initButt() {
  pinMode(10, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

void waitWhite() {
  while (digitalRead(12))
    ;
  while (!digitalRead(12))
    ;
}