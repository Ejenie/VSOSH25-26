#pragma once
//вкладка для работы с кнопками

void _initButt() {
  pinMode(10, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

bool waitWhite() {
  while (digitalRead(12)) {
    return false;
  }
  while (!digitalRead(12))
    ;
  return true;
}

void reset() {
  if (waitWhite()) {
    texst("reboot", 3, 15);
    delay(2000);
    asm volatile("jmp 0x00");
  }
}

bool waitGreen() {
  while (digitalRead(10)) {
    return false;
  }
  while (!digitalRead(10))
    ;
  return true;
}