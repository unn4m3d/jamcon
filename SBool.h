#ifndef __SBOOL_H
#define __SBOOL_H

#include "SButton.h"

class SBool
{
public:
  void draw(Adafruit_GFX *d)
  {
    blink = !blink;
    if(value)
      tV->draw(d,WHITE,blink && active ? WHITE : BLACK);
    else
      fV->draw(d,WHITE,blink && active ? WHITE : BLACK);
  }

  bool getValue()
  {
    return value;
  }

  void setValue(bool b)
  {
    value = b;
  }

  void setActive(bool b)
  {
    active = b;
  }

  void keyPress(char k)
  {
    if(!active) return;
    if(k == '0' || k == '#')
      value = false;
    else if(k == '1' || k == '*')
      value = true;
  }

  SBool(bool value, SBContent *t, SBContent *f)
  {
    this->value = value;
    tV = t;
    fV = f;
  }
private:
  bool value,blink,active;
  SBContent *tV, *fV;
};

#endif // __SBOOL_H
