#include <LiquidCrystal.h>
//#include <Adafruit_LiquidCrystal.h>
byte spg[8] = {
  0b00011,
  0b00111,
  0b01111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte spd[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b01111,
  0b00111,
  0b00011
};
byte slg[8] = {
  0b11000,
  0b11100,
  0b11110,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte sld[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11110,
  0b11100,
  0b11000
};
byte kg[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte kd[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte pr[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte ks[8] = {
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000
};

void CreateCustomChar(LiquidCrystal& lcd){
//void CreateCustomChar(Adafruit_LiquidCrystal& lcd){
  lcd.createChar(0, spg); //lcd.write((byte)0);
  lcd.createChar(1, spd); //lcd.write(byte(1));
  lcd.createChar(2, slg); //lcd.write(byte(2));
  lcd.createChar(3, sld); //lcd.write(byte(3));
  lcd.createChar(4, kg); //lcd.write(byte(4));
  lcd.createChar(5, kd); //lcd.write(byte(5));
  lcd.createChar(6, pr); //lcd.write(byte(6));
  lcd.createChar(7, ks); //lcd.write(byte(7));
  lcd.clear();
}

void buildNum(LiquidCrystal& lcd,const int& p, const int& i){
  switch(i){
    case 0:
      lcd.setCursor(p, 0);
      lcd.write((byte)0);
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(255);
      lcd.print(" ");
      lcd.write(255);
      lcd.setCursor(p, 2);
      lcd.write(byte(1));   
      lcd.write(byte(5));   
      lcd.write(byte(3));
    break;
    case 1:
      lcd.setCursor(p, 0);
      lcd.write((byte)0);
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(" ");
      lcd.print(" ");
      lcd.write(255);
      lcd.setCursor(p, 2);
      lcd.print(" ");
      lcd.print(" ");   
      lcd.write(byte(3));
    break;
    case 2:
      lcd.setCursor(p, 0);
      lcd.write(byte(1));
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(byte(5));
      lcd.write(byte(7));
      lcd.write(byte(4));
      lcd.setCursor(p, 2);
      lcd.write(byte(6));   
      lcd.write(byte(5));   
      lcd.write(byte(2));
    break;
    case 3:
      lcd.setCursor(p, 0);
      lcd.write(byte(3));   
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(byte(7));   
      lcd.write(byte(7));   
      lcd.write(byte(6));
      lcd.setCursor(p, 2);
      lcd.write(byte(2));   
      lcd.write(byte(5));   
      lcd.write(byte(3));
    break;
    case 4:
      lcd.setCursor(p, 0);
      lcd.write(byte(2));
      lcd.print(" ");   
      lcd.write(byte(0));
      lcd.setCursor(p, 1);
      lcd.write(byte(4));
      lcd.write(byte(7));   
      lcd.write(byte(6));
      lcd.setCursor(p, 2);
      lcd.print(" ");
      lcd.print(" ");
      lcd.write(byte(3));
    break;
    case 5:
      lcd.setCursor(p, 0);
      lcd.write(byte(6));
      lcd.write(byte(4));   
      lcd.write(byte(4));
      lcd.setCursor(p, 1);
      lcd.write(byte(4));
      lcd.write(byte(4));
      lcd.write(byte(2));
      lcd.setCursor(p, 2);
      lcd.write(byte(2));
      lcd.write(byte(5));
      lcd.write(byte(3));
    break;
    case 6:
      lcd.setCursor(p, 0);
      lcd.write(byte(0));
      lcd.write(byte(4));   
      lcd.write(byte(1));
      lcd.setCursor(p, 1);
      lcd.write(byte(6));
      lcd.write(byte(2));
      lcd.write(byte(5));
      lcd.setCursor(p, 2);
      lcd.write(byte(1));   
      lcd.write(byte(5));   
      lcd.write(byte(3));
    break;
    case 7:
      lcd.setCursor(p, 0);
      lcd.write(byte(3));
      lcd.write(byte(4));   
      lcd.write(byte(6));
      lcd.setCursor(p, 1);
      lcd.write(byte(5));
      lcd.write(byte(0));
      lcd.write(byte(4));
      lcd.setCursor(p, 2);
      lcd.write(byte(3));   
      lcd.print(" ");
      lcd.print(" ");
    break;
    case 8:
      lcd.setCursor(p, 0);
      lcd.write(byte(0));
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(byte(6));
      lcd.write(byte(7));
      lcd.write(byte(6));
      lcd.setCursor(p, 2);
      lcd.write(byte(1));   
      lcd.write(byte(5));   
      lcd.write(byte(3));
    break;
    case 9:
      lcd.setCursor(p, 0);
      lcd.write(byte(0));
      lcd.write(byte(4));   
      lcd.write(byte(2));
      lcd.setCursor(p, 1);
      lcd.write(byte(4));
      lcd.write(byte(7));   
      lcd.write(byte(6));
      lcd.setCursor(p, 2);
      lcd.write(byte(2));
      lcd.write(byte(5));
      lcd.write(byte(3));
    break;
  }
}

void showNum(LiquidCrystal& lcd,const int& pos, const int& num){
  int l1=0,l2=0;
  l1=num/10;
  l2=num%10;
  buildNum(lcd,pos,l1);
  buildNum(lcd,pos+3,l2);
}

void dzienTygodnia(LiquidCrystal& lcd, const int& i){
  switch(i){
    case 1:
      lcd.print("Nd");
    break;
    case 2:
      lcd.print("Pn");
    break;
    case 3:
      lcd.print("Wt");
    break;
    case 4:
      lcd.print("Sr");
    break;
    case 5:
      lcd.print("Cz");
    break;
    case 6:
      lcd.print("Pt");
    break;
    case 7:
      lcd.print("So");
    break;
  }
}

void miesiac(LiquidCrystal& lcd, const int& i){
  switch(i){
    case 1:
      lcd.print("I");
    break;
    case 2:
      lcd.print("II");
    break;
    case 3:
      lcd.print("III");
    break;
    case 4:
      lcd.print("IV");
    break;
    case 5:
      lcd.print("V");
    break;
    case 6:
      lcd.print("VI");
    break;
    case 7:
      lcd.print("VII");
    break;
    case 8:
      lcd.print("VIII");
    break;
    case 9:
      lcd.print("IX");
    break;
    case 10:
      lcd.print("X");
    break;
    case 11:
      lcd.print("XI");
    break;
    case 12:
      lcd.print("XII");
    break;
  }
}
