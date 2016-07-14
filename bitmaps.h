#ifndef __BITMAPS_H
#define __BITMAPS_H

#define BITMAP const PROGMEM static unsigned char 

BITMAP logo[] = { //Битмап с логотипом
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000,
  B11100010,B00101101,B01110111,B01000100,
  B11111010,B10100111,B01010101,B01000100,
  B11111010,B10101001,B01000101,B01000100,
  B11111010,B00101101,B01000101,B01100100,
  B11111010,B10101101,B01000101,B01010100,
  B10111010,B10101101,B01010101,B01001100,
  B10000010,B10101101,B01110111,B01000100,
  B11111111,B11111100,B00000000,B00000000,
  B11111111,B11111100,B00000000,B00000000
};

const static int logo_width = 4;
const static int logo_height = 15;

// Битмап для кнопки настроек
BITMAP s_bmp[] = {
  B00100100,
  B00111100,
  B11111111,
  B01100110,
  B01100110,
  B11111111,
  B00111100,
  B00100100
};

// Битмап для кнопки OK
BITMAP ok_bmp[] = {
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
BITMAP cn_bmp[] = {
  B11000011,
  B11100111,
  B01111110,
  B00111100,
  B00111100,
  B01111110,
  B11100111,
  B11000011
};

BITMAP gr_bmp[] = {
  B10000000,
  B10000000,
  B10000000,
  B10001000,
  B10110100,
  B11000010,
  B10000000,
  B11111111
};

BITMAP sun_bmp[] = {
  B00010000,
  B01010100,
  B00111000,
  B11111110,
  B00111000,
  B01010100,
  B00010000
};

BITMAP moon_bmp[] = {
  B11111111,
  B11000011,
  B10111101,
  B10111001,
  B10110001,
  B10100001,
  B11000011,
  B11111111
};

BITMAP snd_bmp[] = {
  B00000110,
  B00001010,
  B01110010,
  B01000010,
  B01000010,
  B01110010,
  B00001010,
  B00000110
};

BITMAP nosnd_bmp[] = {
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

SBBitmap<8,8> sn_icon = SBBitmap<8,8>(snd_bmp);
SBBitmap<8,8> ns_icon = SBBitmap<8,8>(nosnd_bmp);

SBText a_icon = SBText("A");
SBText st_icon = SBText("S");
SBText n_icon = SBText(">");
SBText p_icon = SBText("<");
#ifdef USE_P_T_BITMAPS
  BITMAP temp_bmp[] = {
    B01111000,
    B01010000,
    B01011000,
    B01010000,
    B01010000,
    B01010000,
    B11111000,
    B11111000,
    B11111000
  };

  SBBitmap<5,9> temp_icon(temp_bmp);

  BITMAP pressure_bmp[] = {
    B00111100,
    B01000010,
    B11100001,
    B10111001,
    B10011001,
    B10010001,
    B01100010,
    B00111100
  };

  SBBitmap<8,8> pressure_icon(pressure_bmp);
#else
  SBText pressure_icon("P"); //TODO Icons
  SBText temp_icon("T");
#endif // USE_P_T_BITMAPS
#endif // __BITMAPS_H
