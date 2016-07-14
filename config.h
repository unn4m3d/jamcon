/*************************************\
 * Конфиг скетча.
 * 
\*************************************/

#ifndef __CONFIG_H
#define __CONFIG_H
/* Версия скетча. Отображается на About Screen */
#define VERSION "0.1.2"
/* Пин светодиода индикации нагрузки (мигает при записи результатов на SD карту) */
#define LOAD_LED_PIN    48
/* Пин светодиода индикации ошибки */
#define ERR_LED_PIN     47
/* Пины дисплея (CLK, DIN, DC, CE, RST) */
#define DISP_PINS       30,31,32,33,34
/* SS (CS) пин модуля SD-карты */
#define SDCARD_SS_PIN   46
/* Пины клавиатуры */
#define KEYPAD_R_PINS   22,23,24,25
#define KEYPAD_C_PINS   26,27,28,29
/* Количество строк на клавиатуре */
#define KEYPAD_ROWS     4
/* Количество столбцов на клавиатуре */
#define KEYPAD_COLS     4
/* Пин пьезоэлемента */
#define BUZZER_PIN      35
/* Пин реле */
#define RELAY_PIN       36

#endif
