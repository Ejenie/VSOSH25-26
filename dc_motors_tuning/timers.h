void smart_timer(uint32_t time_d) {
  static uint32_t timer;
  while (micros() - timer < time_d);
  timer = micros();
}
