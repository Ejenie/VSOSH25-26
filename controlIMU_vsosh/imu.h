#include <Wire.h>

#define BNO_ADDR 0x29         // I2C адрес BNO055 (0x28 или 0x29)
#define BNO_CHIP_ID_REG 0x00  // Регистр идентификации (должен вернуть 0xA0)
double dataIMUreal[3] = { 0, 0, 0 };

void writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(BNO_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
  delay(30);
}

// Функция чтения нескольких регистров подряд
void readRegs(uint8_t reg, uint8_t *buf, uint8_t len) {
  Wire.beginTransmission(BNO_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)BNO_ADDR, (uint8_t)len);
  for (uint8_t i = 0; i < len; i++) {
    buf[i] = Wire.read();
  }
}

// --- Функция чтения всех данных ---
void updateIMU(double *data) {
  uint8_t buffer[8];

  // Регистр 0x1A: Эйлеровы углы (H,R,P). 1 LSB = 1/16 Degree
  readRegs(0x1A, buffer, 6);
  for (int i = 0; i < 3; i++) data[i] = (int16_t)((buffer[i * 2 + 1] << 8) | buffer[i * 2]) / 16.0;
}


void _checkIMU(double *data) {
  updateIMU(dataIMUreal);

  Serial.print("Heading:");
  Serial.println(data[0]);
}

void _initIMU() {
  Wire.begin();

  // Проверка связи с датчиком, остановит программу если BNO055 не найден
  uint8_t id;
  readRegs(BNO_CHIP_ID_REG, &id, 1);
  if (id != 0xA0) {
    Serial.println("Ошибка: BNO055 не найден!");
    while (1)
      ;
  }

  // Настройка датчика
  writeReg(0x3D, 0x00);  // OPR_MODE: CONFIGMODE (нужен для настройки)
  writeReg(0x3F, 0x20);  // SYS_TRIGGER: Сброс системы
  delay(700);            // Время на перезагрузку

  writeReg(0x3B, 0x00);  // UNIT_SEL: m/s2, Dps, Degrees, Celsius (выбор единиц измерения)
  writeReg(0x3D, 0x0C);  // OPR_MODE: NDOF (Sensor Fusion включен)
  delay(100);
}
double dataIMU = 0;
double deltaIMU = 0;

double delta(double n, double m) {
  
}

void updateDelta() {
  deltaIMU = delta(dataIMU, dataIMUreal[0]);
}

void zeroIMU() {
  dataIMU = dataIMUreal[0];
  updateDelta();
}