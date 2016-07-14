#ifndef __SBUTTON_H
#define __SBUTTON_H
class SBContent
{
public:
  virtual void draw(Adafruit_GFX *d,byte bg, byte fg, int x, int y,int w, int h);
  virtual void draw(Adafruit_GFX *d, byte bg, byte fg, int w, int h)
  {
    draw(d,bg,fg,d->getCursorX(),d->getCursorY(),w,h);
  }
  virtual void draw(Adafruit_GFX *d,byte bg, byte fg)
  {
    draw(d,bg,fg,width(d)+2,height(d)+2);
  }
  virtual int width(Adafruit_GFX *d);
  virtual int height(Adafruit_GFX *d);
};

class SBText : public SBContent
{
public:
  void draw(Adafruit_GFX *d,byte bg, byte fg, int x, int y,int w, int h){
    //d->drawRect(x,y,w,h,fg);
    d->fillRect(x,y,w,h,bg);
    d->setTextColor(fg);
    d->setCursor(x+2,y+1);
    d->print(this->text);
  }

  int width(Adafruit_GFX *d)
  {
    int tx,ty;
    unsigned tw,th;
    d->getTextBounds((char*)text.c_str(),0,0,&tx,&ty,&tw,&th);
    return tw;
  }

  int height(Adafruit_GFX *d)
  {
    int tx,ty;
    unsigned tw,th;
    d->getTextBounds((char*)text.c_str(),0,0,&tx,&ty,&tw,&th);
    return th;
  }

  SBText(String t){
    this->text = t;
  }

private:
  String text;
};

template<int bw, int bh> class SBBitmap : public SBContent
{
public:
  void draw(Adafruit_GFX *d,byte bg, byte fg, int x, int y,int w, int h)
  {
    //d->drawRect(x,y,w,h,fg);
    d->fillRect(x,y,w,h,bg);
    d->drawBitmap(
      x + (w-bw)/2,
      y + (h-bh)/2,
      this->bitmap,
      ceil(bw/8.0)*8,
      bh,
      fg
    );
  }

  int height(Adafruit_GFX *d)
  {
    return bh;
  }

  int width(Adafruit_GFX *d)
  {
    return bw;
  }

  SBBitmap(const unsigned char b[bw*bh/8])
  {
    bitmap = b;
  }
private:
  unsigned char const *bitmap;

};

class SButton
{
public:
  void setFg(byte b)
  {
    fg = b;
  }

  void setBg(byte b)
  {
    bg = b;
  }

  void draw(Adafruit_GFX *d,int x,int y,int w,int h)
  {
    if(content != 0){
      content->draw(d,bg,fg,x,y,w,h);
    }
  }

  SButton(byte bg, byte fg, SBContent *c)
  {
    this->bg = bg;
    this->fg = fg;
    this->content = c;
  }
  

private:
  SBContent *content;
  byte fg,bg;
};
#endif // __SBUTTON_H
