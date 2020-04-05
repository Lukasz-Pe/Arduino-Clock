#include "bigChar.h"
#include "ClickEncoder.h"
#include "TimerOne.h"
#include<DS3231.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int  beep = 37, ent = 35, rl = 33, rr = 31, res = 41;
const int rs = 16, en = 17, d4 = 23, d5 = 25, d6 = 27, d7 = 29;
DS3231 rtc(SDA,SCL);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int g=0,m=0,s=0,dzi=1,mie=1,rok=2020;
int p=0;
Time t;

//Zmienne dla menu
int i=0;
int menuitem = 0;
int frame = 0;
int lastFrame=-1;
int page = 1;
int lastMenuItem = -1;
bool up = false;
bool down = false;
bool middle = false;
int lastSec=s;

//Teksty dla menu:
String menuItem[] = {"Ustaw rok","Ustaw m-c","Ustaw dzien","Ustaw godzine","Ustaw minute","Ustaw sekunde","Wyjdz"};
int menuItemSize=sizeof(menuItem)/sizeof(String);

//Definicja enkodera
ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
  encoder->service();
}

void setup() {
  rtc.begin();
  //ustawienie enkodera
  encoder = new ClickEncoder(rl, rr, ent);
  encoder->setAccelerationEnabled(false);
  //ustawienie przerwań dla enkodera
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  //Ustawienie ostatniej wartości enkodera
  last = encoder->getValue();
  t=rtc.getTime();
  g=t.hour;
  m=t.min;
  s=t.sec;
  dzi=t.date;
  mie=t.mon;
  rok=t.year;
  lcd.begin(20,4);
  CreateCustomChar(lcd);
  //setTime(g, m, s, dzi, mie, rok);
  // Print a message to the LCD.
  //pinMode(ent, INPUT_PULLUP);
  //pinMode(rl, INPUT_PULLUP);
  //pinMode(rr, INPUT_PULLUP);
  //pinMode(res, INPUT_PULLUP);
  //pinMode(beep, OUTPUT);
  //digitalWrite(beep,LOW);
  //Serial.begin(9600);
}

//Deklaracje potrzebnych funkcji
void mainMenu();
void displayMenuItem(const String& item, const int& posx, const int& posy, const bool& selected);
void displayIntMenuPage(const String& menuItem, int& value);
void menuSelect();
void readRotaryEncoder();
void showValue(const int& item, const int& pos, const bool& active=false);
void changeValue();
bool leapYear(const int& year);

void showTime(){
    p=0;
  showNum(lcd,p,t.hour);
  if(t.sec%2==0){
    lcd.setCursor(6,1);
    lcd.print(" ");
    lcd.setCursor(6,0);
    lcd.write(byte(5));
    lcd.setCursor(6,2);
    lcd.write(byte(4));
  }else{
    lcd.setCursor(6,0);
    lcd.print(" ");
    lcd.setCursor(6,2);
    lcd.print(" ");
    lcd.setCursor(6,1);
    lcd.write(byte(7));
  }
  p+=7;
  showNum(lcd,p,t.min);
  if(t.sec%2!=0){
    lcd.setCursor(13,1);
    lcd.print(" ");
    lcd.setCursor(13,0);
    lcd.write(byte(5));
    lcd.setCursor(13,2);
    lcd.write(byte(4));
  }else{
    lcd.setCursor(13,0);
    lcd.print(" ");
    lcd.setCursor(13,2);
    lcd.print(" ");
    lcd.setCursor(13,1);
    lcd.write(byte(7));
  }
  p+=7;
  showNum(lcd,p,t.sec);
  lcd.setCursor(0,3);
  dzienTygodnia(lcd, t.dow);
  lcd.print(", ");
  if(t.date<10){
    lcd.print("0");
  }
  lcd.print(t.date);
  lcd.setCursor(7,3);
  miesiac(lcd, t.mon);
  lcd.setCursor(13,3);
//  lcd.print(t.year);
//  lcd.setCursor(15,3);
//  lcd.print("T=");
  lcd.print(rtc.getTemp());
  lcd.print((char)223);
  lcd.print("C");
}

bool menu=false;
int option=-1;
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
  t=rtc.getTime();
  ClickEncoder::Button b = encoder->getButton();
  if(b != ClickEncoder::Open){
    middle=true;
  }
  if(!menu){
    showTime();
    if(middle){
      middle=false;
      menu=true;
      lcd.clear();
    }
    if((t.hour==0)&&(t.min==0)&&(t.sec==0)/*||(digitalRead(res)==LOW)*/){
      //digitalWrite(beep,HIGH);
      delay(995);
      resetFunc();
    }
  }else{
    readRotaryEncoder();
    mainMenu();
    if(up||down||middle){
      up=false;
      down=false;
      middle=false;
    }
  }
}

void mainMenu(){
  if(page==1){
    if(down){
      menuitem++;
    }
    if(up){
      menuitem--;
    }
    if(menuitem<0){
      menuitem=6;
    }
    if(menuitem>6){
      menuitem=0;
    }
    lcd.setCursor(7,0);
    lcd.print("MENU");
    if(lastSec!=t.sec){
      lcd.clear();
        int prev=0, next=0;
        if((menuitem-1)<0){
          prev=menuItemSize-1;
        }else{
          prev=menuitem-1;
        }
        if((menuitem+1)>(menuItemSize-1)){
          next=(menuItemSize-1)-menuitem;
        }else{
          next=menuitem+1;
        }
        displayMenuItem(menuItem[prev],0,1,false);
        showValue(prev,1);
        displayMenuItem(menuItem[menuitem],0,2,true);
        showValue(menuitem,2);
        displayMenuItem(menuItem[next],0,3,false);
        showValue(next,3);
      lastSec=t.sec;
    }
    if(middle){
      if(menuitem!=6){
        page=2;
      }else{
        lcd.clear();
        menu=false;
      }
    }
  }else if(page==2){
    lcd.setCursor(7,0);
    lcd.print("MENU");
    if(up||down){
      lcd.clear();
        int prev=0, next=0;
        if((menuitem-1)<0){
          prev=menuItemSize-1;
        }else{
          prev=menuitem-1;
        }
        if((menuitem+1)>(menuItemSize-1)){
          next=(menuItemSize-1)-menuitem;
        }else{
          next=menuitem+1;
        }
        displayMenuItem(menuItem[prev],0,1,false);
        showValue(prev,1);
        displayMenuItem(menuItem[menuitem],0,2,true);
        lcd.setCursor(0,2);
        lcd.write(255);
        showValue(menuitem,2,true);
        displayMenuItem(menuItem[next],0,3,false);
        showValue(next,3);
    }
    if(middle){
      rtc.setTime(g, m, s);
      rtc.setDate(dzi, mie, rok);
      rtc.setDOW();
      page=1;
    }
  }
}

void displayMenuItem(const String& item, const int& posx, const int& posy, const bool& selected){
    lcd.setCursor(posx, posy);
    if(selected){
      lcd.print(">"+item);
    }else{
      lcd.print(" "+item);
    }
}

void readRotaryEncoder(){
  value += encoder->getValue();
  
  if (value/4 > last) {
    last = value/4;
    down = true;
    lcd.clear();
  }else   if (value/4 < last) {
    last = value/4;
    up = true;
    lcd.clear();
  }
}

void displayIntMenuPage(const String& menuItem, int value){
    lcd.setCursor(3,3);
    lcd.print(menuItem);
    showNum(lcd,7,value);
}

void showValue(const int& item, const int& pos, const bool& active=false){
  lcd.setCursor(16,pos);
  if(page==1){
    switch(item){
      case 0:
        rok=t.year;
        lcd.print(rok);
      break;
      case 1:
        mie=t.mon;
        miesiac(lcd,mie);
      break;
      case 2:
        dzi=t.date;
        if(dzi<10){
          lcd.print("0");
          lcd.print(dzi);
        }else{
          lcd.print(dzi);
        }
      break;
      case 3:
        g=t.hour;
        if(g<10){
          lcd.print("0");
          lcd.print(g);
        }else{
          lcd.print(g);
        }
      break;
      case 4:
        m=t.min;
        if(m<10){
          lcd.print("0");
          lcd.print(m);
        }else{
          lcd.print(m);
        }
      break;
      case 5:
        s=t.sec;
        if(s<10){
          lcd.print("0");
          lcd.print(s);
        }else{
          lcd.print(s);
        }
      break;
    }
  }else if(page==2&&active){
    switch(item){
      case 0:
        if(down){
          rok++;
        }
        if(up){
          rok--;
        }
        lcd.print(rok);
      break;
      case 1:
        if(down){
          mie++;
        }
        if(up){
          mie--;
        }
        if(mie<1){
          mie=12;
        }else if(mie>12){
          mie=1;
        }
        miesiac(lcd,mie);
      break;
      case 2:
        if(down){
          dzi++;
        }
        if(up){
          dzi--;
        }
        switch(mie){
          case 1:
          case 3:
          case 5:
          case 7:
          case 8:
          case 10:
          case 12:
            if(dzi<0){
              dzi=31;
            }else if(dzi>31){
              dzi=1;
            }
            break;
          case 2:
            if(leapYear(t.year)){
              if(dzi>29){
                dzi=1;
              }
              if(dzi<0){
                dzi=29;
              }
            }else{
              if(dzi>28){
                dzi=1;
              }
              if(dzi<1){
                dzi=28;
              }
            }
            break;
          case 4:
          case 6:
          case 9:
          case 11:
            if(dzi<0){
              dzi=30;
            }else if(dzi>30){
              dzi=1;
            }
            break;
        }
        if(dzi<10){
          lcd.print("0");
          lcd.print(dzi);
        }else{
          lcd.print(dzi);
        }
      break;
      case 3:
        if(down){
          g++;
        }
        if(up){
          g--;
        }
        if(g<0){
          g=23;
        }else if(g>23){
          g=0;
        }
        if(g<10){
          lcd.print("0");
          lcd.print(g);
        }else{
          lcd.print(g);
        }
      break;
      case 4:
        if(down){
          m++;
        }
        if(up){
          m--;
        }
        if(m<0){
          m=59;
        }else if(m>59){
          m=0;
        }
        if(m<10){
          lcd.print("0");
          lcd.print(m);
        }else{
          lcd.print(m);
        }
      break;
      case 5:
        if(down){
          s++;
        }
        if(up){
          s--;
        }
        if(s<0){
          s=59;
        }else if(s>59){
          s=0;
        }
        if(s<10){
          lcd.print("0");
          lcd.print(s);
        }else{
          lcd.print(s);
        }
      break;
    }
  }
}

bool leapYear(const int& year){
  if(year%4==0&&year%100!=0){
    return true;
  }
  if(year%400==0){
    return true;
  }
  return false;
}
