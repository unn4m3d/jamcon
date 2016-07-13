#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <EEPROM.h>

const int settings_addr = 0;

typedef struct sttngs{
  unsigned morning,evening; // по 11 бит для хранения времени смен дня и ночи
  bool pressureFormat; // 1 - мм рт ст, 0 - Паскаль
  bool mute; // 1 - без звука
} settings_t;

settings_t settings;

void setMorning(byte h, byte m)
{
  if(h >= 0 && h < 24 && m >= 0 && m < 60)
    settings.morning = h*60 + m;
}

void setEvening(byte h, byte m)
{
  if(h >= 0 && h < 24 && m >= 0 && m < 60)
    settings.evening = h*60 + m;
}

void getMorning(byte *h, byte *m)
{
  if(settings.evening == settings.morning)
  {
     *h = 7;
     *m = 0;
  }
  else
  {
    *h = settings.morning / 60;
    *m = settings.morning % 60;
  }
}

void getEvening(byte *h, byte *m)
{
  if(settings.evening == settings.morning)
  {
     *h = 21;
     *m = 0;
  }
  else
  {
    *h = settings.evening / 60;
    *m = settings.evening % 60;
  }
}

void mute()
{
  settings.mute = true;
}

void unmute()
{
  settings.mute = false;
}

bool isMute()
{
  return settings.mute;
}

void saveSettings()
{
    EEPROM.put(settings_addr,settings);
}

void loadSettings()
{
    EEPROM.get(settings_addr,settings);
}

#define SOUND if(!isMute())


#endif // __SETTINGS_H
