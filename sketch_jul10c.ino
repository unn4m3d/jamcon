#include <SD.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <gfxfont.h>
#include <Key.h>
#include <Keypad.h>
#include "config.h"
#include "notes.h"
#include "SButton.h"
#include "settings.h"
#include "timeutils.h"
#include "stringutils.h"
#include "SEditable.h"
#include "bitmaps.h"
#include "SBool.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(DISP_PINS); // Инициализируем дисплей
Adafruit_BMP085 dps = Adafruit_BMP085(); // Объявляем барометр
float t = 0, p = 0;

SButton press_btn(BLACK,WHITE,&pressure_icon);
SButton temp_btn(BLACK,WHITE,&temp_icon);


// Создаем кнопки
SButton s_btn = SButton(
  BLACK,
  WHITE,
  &s_icon
);


SButton a_btn = SButton(
  BLACK,
  WHITE,
  &a_icon
);

SButton st_btn = SButton(
  BLACK,
  WHITE,
  &st_icon
);

SButton p_btn = SButton(
  BLACK,
  WHITE,
  &p_icon
);

SButton n_btn = SButton(
  BLACK,
  WHITE,
  &n_icon
);

SButton ok_btn = SButton(
  BLACK,
  WHITE,
  &ok_icon
);

SButton cn_btn = SButton(
  BLACK,
  WHITE,
  &cn_icon
);

SButton gr_btn = SButton(BLACK,WHITE,&gr_icon);



char keymap[KEYPAD_ROWS][KEYPAD_COLS]=  // Карта клавиш
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


byte rowPins[KEYPAD_ROWS] = {KEYPAD_R_PINS}; //Строки клавиатуры с 0 по 3
byte colPins[KEYPAD_COLS]= {KEYPAD_C_PINS};  //Колонки с 0 по 3



//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);



bool keyPressed(char k){
  return myKeypad.isPressed(k);
}

#define CMD_BYTE 0x42
#define RES_BYTE 0x43
#define END_BYTE '\n'
#define NO_CMD ""

void sendResponse(String response)
{
  Serial.write(RES_BYTE);
  Serial.write(response.c_str());
  Serial.write(END_BYTE);
}

String readCommand()
{
  byte c = 0;
  if(Serial.available() <= 0 || (c = Serial.read()) != CMD_BYTE) return NO_CMD;
  return Serial.readStringUntil(END_BYTE);
}

bool sdCardPresent = false;

void setup()
{
  Serial.begin(9600);           // Инициализация последовательного порта для дебаггинга
  sendResponse("Initializing");
  display.begin();              // Инициализация дисплея
  display.setContrast(60);      // Устанавливаем контраст
  display.setTextColor(BLACK);  // Устанавливаем цвет текста
  display.setTextSize(1);       // Устанавливаем размер текста
  display.clearDisplay();       // Очищаем дисплей
  display.drawBitmap(           // Рисуем лого
    LCDWIDTH/2-(logo_width*4),
    LCDHEIGHT/2-(logo_height/2),
    logo,
    logo_width*8,
    logo_height,
    BLACK
  );
  display.setCursor(0,0);
  display.print("I2C Init");
  display.fillRect(0,LCDHEIGHT-10,10,9,BLACK);
  display.display();           
  Wire.begin();                 // Инициализация I2C (на ней RTC и барометр)
  delay(250);                  // Ждем инициализации + 900 мс для отображения лого
  display.setCursor(0,0);
  display.fillRect(0,0,LCDWIDTH,8,WHITE);
  display.print("Initializing");
  display.fillRect(0,LCDHEIGHT-10,40,9,BLACK);
  display.display(); 
  delay(250);
  display.fillRect(0,LCDHEIGHT-10,60,9,BLACK);
  display.setCursor(0,0);
  display.fillRect(0,0,LCDWIDTH,8,WHITE);
  display.print("GY-68 Init");
  display.display(); 
  delay(250);           
  dps.begin();                  // Инициализация барометра и термометра
  loadSettings();
  setSyncProvider(RTC.get);     // Устанавливаем RTC как источник времени
  display.fillRect(0,LCDHEIGHT-10,80,9,BLACK);
  display.setCursor(0,0);
  display.fillRect(0,0,LCDWIDTH,8,WHITE);
  display.print("SDCard Init");
  display.display(); 
  delay(250);    
  pinMode(53,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  pinMode(RELAY_PIN,OUTPUT);

  if(sdCardPresent = SD.begin(46))
    sendResponse("SDCard initialized");
  else
    sendResponse("SDCard failed to initialize");
  display.fillRect(0,LCDHEIGHT-10,84,9,BLACK);
  display.display();    
}

char menuButtons[] = {'A','B','C','D'}; // Кнопки меню

void drawMenu(SButton** buttons, byte count)
{

  
  if(count > 4) count = 4;
  display.fillRect(0,0,9,LCDHEIGHT,BLACK);

  for(int i = 0; i < count; i++)
  {

    if(keyPressed(menuButtons[i]))
    {
      buttons[i]->setFg(BLACK);
      buttons[i]->setBg(WHITE);
    }
    else
    {
      buttons[i]->setFg(WHITE);
      buttons[i]->setBg(BLACK);
    }
    buttons[i]->draw(&display,0,LCDHEIGHT/4*i + 1, 9, LCDHEIGHT/4 - 2);
  }
  
  display.drawFastHLine(0,LCDHEIGHT/4,9,WHITE);
  display.drawFastHLine(0,LCDHEIGHT*2/4,9,WHITE);
  display.drawFastHLine(0,LCDHEIGHT*3/4,9,WHITE);
}

void setTimeElem(TimeElements *t, byte num, int val)
{
  switch(num)
  {
    case 0:
      t->Day = val;
      break;
    case 1:
      t->Month = val;
      break;
    case 2:
      t->Year = val;
      break;
    case 3:
      t->Hour = val;
      break;
    case 4:
      t->Minute = val;
      break;
    case 5:
      t->Second = val;
      break;
  }
}



enum InfoScreen{Main,Graph,Settings,Stats,About};

InfoScreen currentScreen = Main;

void drawMainScreen()
{ 
  p = dps.readPressure();
  t = dps.readTemperature();

  SButton* buttons[] = {&s_btn,&gr_btn,&st_btn,&a_btn};
  drawMenu(buttons,4);

  display.setTextColor(BLACK);

  display.setCursor(10,20);
  display.print(padLeft(String(day()),2) + "." + padLeft(String(month()),2)+ "." + padLeft(String(year()),4));

  display.setCursor(10,30);
  display.print(padLeft(String(hour()),2) + ":" + padLeft(String(minute()),2) + ":" + padLeft(String(second()),2));

  display.setTextColor(BLACK);
    
  display.setCursor(10, 0);
  display.print(String(t) + " C");

  display.setCursor(10,10);
  if(settings.pressureFormat)
    display.print(String(long(p)*760.0/101325.0) + "mmHg");
  else
    display.print(String(long(p)) + " Pa");

  display.setCursor(10,40);
  display.print("SDCard ");
  display.print(sdCardPresent ? "OK" : "FAIL");

  NIGHT
  {
    moon_icon.draw(&display, WHITE, BLACK, LCDWIDTH-8, 0, 8 , 8);
  }

  DAY
  {
    sun_icon.draw(&display, WHITE, BLACK, LCDWIDTH-8, 0, 8 , 8);
  }

  SOUND
  {
    sn_icon.draw(&display, WHITE, BLACK, LCDWIDTH-8,9,8,8);
  }
  else
  {
    ns_icon.draw(&display, WHITE, BLACK, LCDWIDTH-8,9,8,8);
  }

  if(keyPressed('A'))
  {
    currentScreen = Settings;
  }
  else if(keyPressed('B'))
  {
    currentScreen = Graph;
  }
  else if(keyPressed('C'))
  {

  }
  else if(keyPressed('D'))
  {
    currentScreen = About;
  }
  display.display();
}

bool graphLoaded = false, graphError = true;
byte graph[LCDWIDTH-10][2];

template<typename T, int N> void pushToSR(T arr[N], T value)
{
  for(int i = 0; i < N; i++)
  {
    if(i == N-1)
    {
      arr[i] = value;
    }
    else
    {
      arr[i] = arr[i+1];
    }
  }
}

void progress(int percentage, String label)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(label + " ");
  display.print(percentage);
  display.print("%");
  display.drawRect(0,10,LCDWIDTH,5,BLACK);
  display.fillRect(0,11,LCDWIDTH*percentage/100, 3, BLACK);
  display.display();
}

void drawGraph()
{
  if(!graphLoaded)
  {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Loading...");
    display.display(); 

    if(sdCardPresent)
    {
      String lines[LCDWIDTH-10];
      File stats = SD.open("BMPS.CSV",FILE_READ);
      if(stats)
      {
        for(int i = 0; i < LCDWIDTH-10 && stats.available(); i++)
        {
          lines[i] = stats.readStringUntil('\n');
          progress(100*stats.position()/stats.size(),"Reading");
        }
        while(stats.available())
        {
          pushToSR<String,LCDWIDTH-10>(lines,stats.readStringUntil('\n'));
          progress(100*stats.position()/stats.size(),"Reading");
        }
        stats.close();
        float p = 0;
        progress((int)p,"Parsing");
        float gdata[LCDWIDTH-10][2];
        for(int i = 0; i < LCDWIDTH-10; i++)
        {
          if(lines[i] == 0) continue;
          p += 0.3;
          progress((int)p,"Parsing");
          float cp = lines[i].substring(lines[i].lastIndexOf(",")+1).toFloat();
          lines[i] = lines[i].substring(0, lines[i].lastIndexOf(","));
          float ct = lines[i].substring(lines[i].lastIndexOf(",")+1).toFloat();
          gdata[i][0] = cp;
          gdata[i][0] = ct;
        }

        p = 30;
        progress((int)p,"Parsing");

        float pmx=gdata[0][0],pmn=gdata[0][0];
        float tmx=gdata[0][1],tmn=gdata[0][1];

        for(int i = 0; i < LCDWIDTH-10; i++)
        {
          p += 0.5;
          progress((int)p,"Parsing");

          if(gdata[i][0] != 0)
          {
            pmx = max(pmx,gdata[i][0]);
            pmn = min(pmn,gdata[i][0]);
          }

          if(gdata[i][1] != 0)
          {
            tmx = max(tmx,gdata[i][1]);
            tmn = min(tmn,gdata[i][1]);
          }
        }

        for(int i = 0; i < LCDWIDTH-10; i++)
        {
          p += 0.3;
          progress((int)p,"Parsing");
          graph[i][0] = (byte)map((int)gdata[i][0],pmn,pmx,LCDHEIGHT,1);
          graph[i][1] = (byte)map((int)gdata[i][1],tmn,tmx,LCDHEIGHT,1);
        }

        progress(100,"Parsing");
        delay(250);

        graphLoaded = true;
        graphError = false;
        
      }
      else
      {
        graphLoaded = true;
        graphError = true;
        digitalWrite(ERR_LED_PIN,HIGH);
        delay(100);
        digitalWrite(ERR_LED_PIN,LOW);
      }
    }
    else
    {
      graphLoaded = true;
      graphError = true;
    }
    
  }
  else
  {
    if(graphError)
    {
      display.clearDisplay();
      display.setCursor(10,0);
      display.print("ERROR");
      display.setCursor(10,10);
      display.print("No SD Card");
      display.setCursor(10,20);
      display.print("or IO Error");
      SButton* btns[] = {&cn_btn};
      drawMenu(btns,1);
      if(keyPressed('A'))
        currentScreen = Main;
      display.display();
    }
    else
    {
      static byte choice = 0;
      display.clearDisplay();
      SButton* btns[] = {&ok_btn,&cn_btn,(choice ? &press_btn : &temp_btn) };
      drawMenu(btns,3);
      for(int i = 1; i < LCDWIDTH-10; i++)
      {
        if(graph[i][choice] == 0)
          break;
        //sendResponse(String(graph[i][0]));
        //sendResponse(String(graph[i][1]));
        display.drawLine(i+9,graph[i-1][choice]-1,i+10,graph[i][choice]-1,BLACK);
      }
      display.display();

      if(keyPressed('A'))
      {
        currentScreen = Main;
      }
      else if(keyPressed('B'))
      {
        currentScreen = Main;
        graphLoaded = false;
      }
      else if(keyPressed('C'))
      {
        choice = (choice ? 0 : 1);
      }
    }
  }
}

void drawAboutScreen()
{
  SButton* buttons[] = {&cn_btn};
  display.clearDisplay();
  drawMenu(buttons,1);
  display.setCursor(10,0);
  display.print("(c) unn4m3d");
  display.setCursor(10,10);
  display.print("Built at");
  display.setCursor(10,20);
  display.print(__DATE__);
  display.setCursor(10,30);
  display.print(__TIME__);
  display.setCursor(10,40);
  display.print("v");
  display.print(VERSION);
  display.display();
  if(keyPressed('A')){
    currentScreen = Main;
  }
}

char lastKey = NO_KEY;

void drawSettings()
{
  static SEditable<byte,23,2>
    eh_ed = SEditable<byte,23,2>(settings.evening/60),
    mh_ed = SEditable<byte,23,2>(settings.morning/60);

  static SEditable<byte,59,2>
    em_ed = SEditable<byte,59,2>(settings.evening%60),
    mm_ed = SEditable<byte,59,2>(settings.morning%60);

  static SBText mmhg("Hg"),pas("Pa");

  static SBool
    sndchk(!settings.mute,&sn_icon,&ns_icon),
    pfchk(settings.pressureFormat,&mmhg,&pas);

  static signed char edit = 0;

  eh_ed.setActive(edit == 3);
  mh_ed.setActive(edit == 1);
  em_ed.setActive(edit == 4);
  mm_ed.setActive(edit == 2);
  sndchk.setActive(edit == 5);
  pfchk.setActive(edit == 6);

  display.setTextColor(BLACK);
  display.clearDisplay();
  display.setCursor(10,0);
  display.print("N->D");
  display.setCursor(10,10);
  mh_ed.draw(&display);
  display.print(":");
  mm_ed.draw(&display);
  display.setCursor(10,20);
  display.print("D->N");
  display.setCursor(10,30);
  eh_ed.draw(&display);
  display.print(":");
  em_ed.draw(&display);
  display.setCursor(10,40);
  sndchk.draw(&display);
  display.setCursor(25,40);
  pfchk.draw(&display);

  SButton* buttons[] = {&p_btn,&n_btn,&cn_btn,&ok_btn};
  drawMenu(buttons,4);

  display.display();

  if(keyPressed('A'))
  {
    edit--;
    if(edit < 0)
      edit = 6;
  }
  else if(keyPressed('B'))
  {
    edit++;
    edit%=7;
  }
  else if(keyPressed('C'))
  {
    currentScreen = Main;
    eh_ed.setValue(settings.evening/60);
    em_ed.setValue(settings.evening%60);
    mh_ed.setValue(settings.morning/60);
    mm_ed.setValue(settings.morning%60);
    sndchk.setValue(!settings.mute);
    pfchk.setValue(settings.pressureFormat);
  }
  else if(keyPressed('D'))
  {
    setMorning(mh_ed.getValue(),mm_ed.getValue());
    setEvening(eh_ed.getValue(),em_ed.getValue());
    sndchk.getValue() ? unmute() : mute();
    settings.pressureFormat = pfchk.getValue();
    saveSettings();
    currentScreen = Main;
  }
  else
  {
    if(lastKey != NO_KEY && (lastKey != '#' || edit ==5 || edit ==6 ))
    {
      mh_ed.keyPress(lastKey);
      mm_ed.keyPress(lastKey);
      eh_ed.keyPress(lastKey);
      em_ed.keyPress(lastKey);
      sndchk.keyPress(lastKey);
      pfchk.keyPress(lastKey);

      switch(edit)
      {
        case 1:
          if(mh_ed.getValue() > 10)
            edit++;
          break;

        case 2:
          if(mm_ed.getValue() > 10)
            edit++;
          break;

        case 3:
          if(eh_ed.getValue() > 10)
            edit++;
          break;

        case 4:
          if(em_ed.getValue() > 10)
            edit++;
          break;
          
        case 5:
          edit++;
          break;
          
        case 6:
          edit = 0;
          break;
      }
    }
  }
}



void loop()
{
  static File stats;
  static String command;
  command = readCommand();
  if(command != NO_CMD)
  {
    time_t timeVal;
    TimeElements te;
    switch(command[0])
    {
      case 'T':
        // TODO : Сделать настройку времени с клавиатуры 
        te.Second = command.substring(16, 18).toInt();
        te.Minute = command.substring(13, 15).toInt();
        te.Hour = command.substring(10, 12).toInt();
        te.Day = command.substring(1, 3).toInt();
        te.Month = command.substring(4, 6).toInt();
        te.Year = command.substring(7, 9).toInt(); + 30;
        timeVal = makeTime(te);
        RTC.set(timeVal);
        setTime(timeVal);
        sendResponse("Time is set");
        break;
      case 'C':
        stats = SD.open("BMPS.CSV",FILE_READ);
        if(stats)
        {
          while(stats.available())
          {
            progress(100*stats.position()/stats.size(),"Sending");
            sendResponse(String("SL ")+stats.readStringUntil('\n'));
          }
          stats.close();
        }
        else
        {
          sendResponse("EL IO ERROR");
        }
        break;
      case 'D':
        sendResponse(String("SP ") + dps.readPressure());
        sendResponse(String("ST ") + dps.readTemperature());
        break;
    }
  }

  static byte frame = 0;
  frame++;
  frame%=16;
  if(frame == 0)
  {
    sendResponse("Opening...");
    if(sdCardPresent)
    {
      stats = SD.open("bmps.csv",FILE_WRITE);
      if(stats)
      {
        sendResponse("Writing...");
        digitalWrite(LOAD_LED_PIN,HIGH);
        stats.print(year());
        stats.print(",");
        stats.print(month());
        stats.print(",");
        stats.print(day());
        stats.print(",");
        stats.print(hour());
        stats.print(",");
        stats.print(minute());
        stats.print(",");
        stats.print(second());
        stats.print(",");
        stats.print(dps.readTemperature());
        stats.print(",");
        stats.println(dps.readPressure());
        stats.close();
        digitalWrite(LOAD_LED_PIN,LOW);
      }
      else
      {
        digitalWrite(ERR_LED_PIN,HIGH);
        sendResponse("Failed to open bmps.csv");
        sdCardPresent = false;
        delay(100);
        digitalWrite(ERR_LED_PIN,LOW);
      }
    }
    else
    {
      //digitalWrite(47,HIGH);
      sendResponse("No SDCard");
     // delay(100);
      //digitalWrite(47,LOW);
    }
  }
  lastKey = myKeypad.getKey();
  if(lastKey != NO_KEY)
  {
    SOUND
    {
      note(BUZZER_PIN,NOTE_D4,8);
    }
  }
  display.clearDisplay();
  switch(currentScreen)
  {
    case Main:
      drawMainScreen();
      break;

    case About:
      drawAboutScreen();
      break;

    case Graph:
      drawGraph();
      break;

    case Settings:
      drawSettings();
      break;
  }
  NIGHT
  {
    digitalWrite(RELAY_PIN,HIGH);
  }
  DAY
  {
    digitalWrite(RELAY_PIN,LOW);
  }
  delay(250);
}


