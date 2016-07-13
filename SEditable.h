#ifndef __SEDITABLE_H
#define __SEDITABLE_H
#include "stringutils.h"

template<typename T, T maxval, int length> class SEditable
{
public:
  T getValue()
  {
    return current_value;
  }

  void setValue(T v)
  {
    current_value = v;
  }

  void keyPress(char k)
  {
    if(!active) return;
    if(isDigit(k))
    {
      T val = current_value;
      val *= 10;
      val += String(k).toInt();
      if(val <= maxval)
      {
        current_value = val;
      }
    }
    else if(k == '*')
    {
      current_value /= 10;
    }
  }

  void draw(Adafruit_GFX *d)
  {
    if(active && blink)
    {
      d->setTextColor(WHITE);
    }
    else
    {
      d->setTextColor(BLACK);
    }
    String s = padLeft(String(current_value),length);
    d->print(s);
    d->setTextColor(BLACK);
    blink = !blink;
  }

  void draw(Adafruit_GFX *d, int x, int y)
  {
    d->setCursor(x,y);
    draw(d);
  }

  void setActive(bool a)
  {
    active = a;
  }

  

  SEditable(T current)
  {
    current_value = current;
    blink = false;
  }
private:
  T current_value;
  
  bool blink;
  bool active = false;
};

#endif // __SEDITABLE_H
