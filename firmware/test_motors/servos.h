#include <Servo.h>
Servo marker;

void _initServos() {
  marker.attach(A0);
}

void up() {
  marker.write(100);
}

void down() {
  marker.write(0);
}