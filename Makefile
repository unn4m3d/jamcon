ifndef BOARD
	BOARD := megaADK
endif

CPPFLAGS += -fno-threadsafe-statics

LIBRARIES := Adafruit_BMP085_Library \
Adafruit_GFX_Library \
Adafruit_PCD8544_Nokia_5110_LCD_library \
Adafruit_Unified_Sensor \
DS1307RTC \
EEPROM \
Keypad/src \
SD \
SPI \
Time \
Wire

include arduino.mk
