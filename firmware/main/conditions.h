#pragma once
//вкладка для переключений состояния галетным переключателем

int32_t condition = -1;

String name[12] = { "one",
                    "test",
                    "3",
                    "4",
                    "5",
                    "6",
                    "7",
                    "8",
                    "9",
                    "10",
                    "11",
                    "12" };

void test() {
  gotoPosRail(rightR, 300);
  downServo();
  gotoPosPlotter(leftP, 300);
  gotoPosPlotter(downP, 300);
  upServo();
  gotoPosRail(leftR, 300);
}

void updateCond() {
  int32_t gal = analogRead(A4);
  if (gal < 540 && gal > 510) {
    condition = 2;
  } else if (gal < 610 && gal > 600) {
    condition = 3;
  } else if (gal < 680 && gal > 660) {
    condition = 4;
  } else if (gal < 770 && gal > 750) {
    condition = 5;
  } else if (gal < 870 && gal > 840) {
    condition = 6;
  } else if (gal == 0) {
    condition = 7;
  } else if (gal < 100 && gal > 60) {
    condition = 8;
  } else if (gal < 170 && gal > 140) {
    condition = 9;
  } else if (gal < 260 && gal > 230) {
    condition = 10;
  } else if (gal < 350 && gal > 320) {
    condition = 11;
  } else if (gal < 430 && gal > 410) {
    condition = 12;
  }
}

void beginCond() {
  updateCond();
  texst((name[condition - 1]), 2, 40, 25);
  delay(FRAME_DELAY);
}

void _readCond() {
  Serial.println(String(analogRead(A4)));
}