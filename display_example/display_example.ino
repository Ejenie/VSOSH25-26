#include <Wire.h>  // Стандартная библиотека работы с I2C
#include "chars.h"
#define OLED_ADDR 0x3C  // Стандартный адрес I2C для SSD1306

void sendCmd(uint8_t command) {  // отправка команд на дисплей
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x80);  // Байт управления: следующая посылка — команда
  Wire.write(command);
  Wire.endTransmission();
}

void setCursor(uint8_t page, uint8_t col) {  // задаем место печати символа
  // в контроллере SSD1306 память 128x64 пикселя разделена на 8 страниц (строк) по 128 столбцов
  sendCmd(0xB0 + page);        // Установка страницы (строки)
  sendCmd(col & 0x0F);         // Столбец (младшие 4 бита)
  sendCmd(0x10 | (col >> 4));  // Столбец (старшие 4 бита)
}

void clear(uint8_t page, uint8_t col) {  // функция очистки с заданного места и до конца строки
  setCursor(page, col);
  Wire.beginTransmission(OLED_ADDR);
  Wire.write(0x40);  // следующий байт (или поток байтов) будет данными пикселей, которые отобразятся на экране
  for (int i = col; i < 128; i++) {
    Wire.write(0);
    if (i > 0 && i % 16 == 0) {  // Каждые 16 байт перезапускаем передачу (защита буфера Wire)
      Wire.endTransmission();
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(0x40);
    }
  }
  Wire.endTransmission();
}

void clear(uint8_t page) {  // очистка строки
  clear(page, 0);
}

void clear() {  // очистка всего экрана
  for (int p = 0; p < 8; p++) {
    clear(p);
  }
}

void printStr(uint8_t page, uint8_t col, const char* s) {  // печать на экран
  setCursor(page, col);
  while (*s && col < 122) {  // Условие: пока есть символы И есть место на экране
    char c = *s;
    if (c >= 'a' && c <= 'z') c -= 32;  // Если строчная буква (a-z), превращаем в заглавную (A-Z)
    int fontIndex = c - 32;
    if (fontIndex < 0 || fontIndex > 58)
      fontIndex = '?' - 32;  // Если символ вне диапазона шрифта заменяем на знак вопроса

    Wire.beginTransmission(OLED_ADDR);  // Печать символа
    Wire.write(0x40);                   // следующий байт (или поток байтов) будет данными пикселей, которые отобразятся на экране
    for (int i = 0; i < 5; i++) {
      Wire.write((font5x7[fontIndex][i]));  // побайтно считываем символы из таблицы
    }
    Wire.write(0x00);  // Межсимвольный интервал 1 столбец
    Wire.endTransmission();

    s++;
    col += 6;  // Сдвигаемся на 5 столюцов буквы + 1 пробел
  }
  clear(page, col);  // стираем остаток строки
}

void printStr(uint8_t page, const char* s) {  // печать с начала строки
  printStr(page, 0, s);
}

void setup() {
  Wire.begin();
  Wire.setClock(40000000);
  // Инициализация SSD1306
  uint8_t init[] = { 0xA8, 0x3F, 0xD3, 0x00,
                     0x40, 0xA1, 0xC8, 0xDA,
                     0x12, 0x02, 0x81, 0x7F,
                     0xA4, 0xA6, 0xD5, 0x80,
                     0x8D, 0x14, 0xAF };
  for (uint8_t i = 0; i < sizeof(init); i++)
    sendCmd(init[i]);

  clear();
}

void loop() {
  char buf[22];  // Тут формируем строку. На экране поместится максимум 22 символа в строке
  snprintf(buf, sizeof(buf), "fold 6");
  printStr(0, buf);  // Выводим строку на экран

  delay(100);
}