#ifndef __TIMEUTILS_H
#define __TIMEUTILS_H

#include "settings.h"

bool gtThan(byte ah, byte am, byte bh, byte bm)
{
  return( ah > bh || (ah == bh && am > bm));
}

bool isInRange(byte sh, byte sm, byte eh, byte em, byte h, byte m)
{
  if(gtThan(sh,sm,eh,em))
    return !isInRange(eh,em,sh,sm,h,m);

  return gtThan(h,m,sh,sm) && gtThan(eh,em,h,m);
}

inline bool isNight()
{
  byte eh,em,mh,mm;
  getEvening(&eh,&em);
  getMorning(&mh,&mm);
  return isInRange(eh,em,mh,mm,hour(),minute());
}

inline bool isDay()
{
  return !isNight();
}

inline byte daysPerMonth(byte m, int y)
{
  byte rawd = 28 + (m + m/8)%2 + 2%m + 2*(1/m);
  bool leap = (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
  if(m == 2 && leap)
    return rawd + 1;
  else
    return rawd;
}

#define NIGHT if(isNight())
#define DAY if(isDay())

#endif // __TIMEUTILS_H
