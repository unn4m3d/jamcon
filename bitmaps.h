#ifndef __BITMAPS_H
#define __BITMAPS_H

const static unsigned char PROGMEM logo[] = { //Битмап с логотипом
  B00011100,B10000001,B11010000,
  B00010100,B10100000,B01010000,
  B10010111,B11111110,B11110000,
  B10100101,B00101010,B01010000,
  B11100101,B00101011,B11110000
};

// Битмап для кнопки настроек
static unsigned char s_bmp[] = {
  B00100100,
  B00111100,
  B11111111,
  B01100110,
  B01100110,
  B11111111,
  B00111100,
  B00100100
};

// Битмап для кнопки настроек времени
static unsigned char c_bmp[] = {
  B00111100,
  B01000010,
  B11100001,
  B10111001,
  B10011001,
  B10010001,
  B01100010,
  B00111100
};

// Битмап для кнопки OK
static unsigned char ok_bmp[] = {
  B00000011,
  B00000011,
  B00000110,
  B10000110,
  B11000110,
  B01101100,
  B00111100,
  B00011000
};

// Битмап для кнопки отмены
static unsigned char cn_bmp[] = {
  B11000011,
  B11100111,
  B01111110,
  B00111100,
  B00111100,
  B01111110,
  B11100111,
  B11000011
};

static unsigned char gr_bmp[] = {
  B10000000,
  B10000000,
  B10000000,
  B10001000,
  B10110100,
  B11000010,
  B10000000,
  B11111111
};

static unsigned char sun_bmp[] = {
  B00010000,
  B01010100,
  B00111000,
  B11111110,
  B00111000,
  B01010100,
  B00010000
};

static unsigned char moon_bmp[] = {
  B11111111,
  B11000011,
  B10111101,
  B10111001,
  B10110001,
  B10100001,
  B11000011,
  B11111111
};

static unsigned char snd_bmp[] = {
  B00000110,
  B00001010,
  B01110010,
  B01000010,
  B01000010,
  B01110010,
  B00001010,
  B00000110
};

static unsigned char nosnd_bmp[] = {
  B10000111,
  B01001110,
  B01110110,
  B01011010,
  B01011010,
  B01110110,
  B01001110,
  B10000111
};

SBBitmap<8,8> gr_icon = SBBitmap<8,8>(gr_bmp);
SBBitmap<7,7> sun_icon = SBBitmap<7,7>(sun_bmp);
SBBitmap<8,8> moon_icon = SBBitmap<8,8>(moon_bmp);
SBBitmap<8,8> ok_icon = SBBitmap<8,8>(ok_bmp);
SBBitmap<8,8> cn_icon = SBBitmap<8,8>(cn_bmp);
SBBitmap<8,8> s_icon = SBBitmap<8,8>(s_bmp);
SBBitmap<8,8> c_icon = SBBitmap<8,8>(c_bmp);

SBBitmap<8,8> sn_icon = SBBitmap<8,8>(snd_bmp);
SBBitmap<8,8> ns_icon = SBBitmap<8,8>(nosnd_bmp);

#endif // __BITMAPS_H
