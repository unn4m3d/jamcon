Just a monitoring microcontroller
==

TODO
--

- Сбор статистики
- Оптимизация
- Измерение влажности
- Стабилизация работы с SD картой
- Настройка времени с клавиатуры

Что умеет
--

- Измеряет температуру и давление
- Может выводить как в Паскалях, так и в мм рт ст (настраивается)
- Работает с SD-картой
- Может строить графики по данным с SD-карты
- Работает с 4x4 Keypad
- Переключает реле в зависимости от "дневного" или "ночного" режимов
- Время переключения настраивается 
- Настройки сохраняются в EEPROM
- Может пищать при нажатии кнопок (настраивается)
- Меню на 4 кнопки (A,B,C,D) слева экрана

Библиотеки
--

1. Adafruit_BMP085_Library
3. Adafruit_GFX_Library
4. Adafruit_PCD8544_Nokia_5110_LCD_library
5. Adafruit_Unified_Sensor
6. DS1307RTC
7. Keypad
8. Time

Hardware
--

1. Arduino Mega 2560, 5V-3.3V конвертер
2. Nokia5110 LCD
	- RST -> D34
	- CE -> D33
	- DC -> D32
	- DIN -> D31
	- CLK -> D30
	- VCC -> 3.3V
	- BL -> 3.3V
	- GND -> GND
3. DS1307 RTC модуль
	- SCL -> D21
	- SDA -> D20
	- VCC -> 5V
	- GND -> GND
4. 4x4 Matrix Keypad
	- D22...D29
5. SDCard модуль
	- MISO -> D50
	- MOSI -> D51
	- SCK -> D52
	- CS -> D46
6. GY-68
	- SCL -> D21
	- SDA -> D20
	- VCC -> 3.3V
	- GND -> GND
7. 2 светодиода
	- D47, D48
8. Пьезоэлемент
	- D35
9. Модуль реле SRD-05VDC0SL-C
	- IN -> D36
	- VCC -> 5V
	- GND -> GND

