#pragma once
//вкладка для переключений состояния галетным переключателем

void _readCond() {
  Serial.println(String(analogRead(A4)) + " " + String(analogRead(A5)));
}