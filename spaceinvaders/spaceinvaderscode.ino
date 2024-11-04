#include <LiquidCrystal.h>
const byte RS = 12;
const byte E = 11;
const byte D4 = 5;
const byte D5 = 4;
const byte D6 = 3;
const byte D7 = 2;
const byte COLS = 16;
const byte ROWS = 2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

int x;
int y;

int tempsBetween = 300 ;

int jumpEntre = 2;
int inverse =  0;

byte invader1Left[8] = {
0b00000100,
0b00000010,
0b00000111,
0b00001101,
0b00011111,
0b00010111,
0b00010100,
0b00000010
};

byte invader1Right[8] = {
0b00000100,
0b00001000,
0b00011100,
0b00010110,
0b00011111,
0b00011101,
0b00000101,
0b00001000
};

byte invader2Left[8] = {
0b00000100,
0b00010010,
0b00010111,
0b00011101,
0b00011111,
0b00001111,
0b00000100,
0b00001000
};

byte invader2Right[8] = {
0b00000100,
0b00001001,
0b00011101,
0b00010111,
0b00011111,
0b00011110,
0b00000100,
0b00000010
};

byte newInvaderLeft[8] = {
0b0000001,
0b0000011,
0b0000111,
0b0001101,
0b0001111,
0b0000010,
0b0000101,
0b0001010
};

byte newInvaderRight[8] = {
0b0010000,
0b0011000,
0b0011100,
0b0010110,
0b0011110,
0b0001000,
0b0010100,
0b0001010
};


void dessinerNewInvader(int x, int y){


  lcd.createChar(4, newInvaderLeft);
  lcd.createChar(5, newInvaderRight);


  lcd.setCursor(x ,y); 
  lcd.write((byte)4);
  lcd.setCursor(x + 1,y);
  lcd.write((byte)5);
  
}

void dessinerInvaderSolo(int x, int y){


  lcd.createChar(0, invader1Left);
  lcd.createChar(1, invader1Right);


  lcd.setCursor(x,y); 
  lcd.write((byte)0);
  lcd.setCursor(x + 1,y);
  lcd.write((byte)1);
  
}


void dessinerInvader1(int x, int y){


  lcd.createChar(0, invader1Left);
  lcd.createChar(1, invader1Right);


  lcd.setCursor(x,y); 
  lcd.write((byte)0);
  lcd.setCursor(x + 1,y);
  lcd.write((byte)1);
  delay(tempsBetween);
  lcd.clear();
  
}


void dessinerInvader2(int x, int y){

  lcd.createChar(2, invader2Left);
  lcd.createChar(3, invader2Right);

  lcd.setCursor(x,y); 
  lcd.write((byte)2);
  lcd.setCursor(x + 1,y);
  lcd.write((byte)3);
  delay(tempsBetween);
  lcd.clear();

}

void setup() {

  lcd.begin(COLS, ROWS);

  if (inverse == 1)
  {
    x = 14;
    y = 1;
    jumpEntre = -2;
  }
}


void loop() {

  dessinerInvader1(x,y), dessinerNewInvader(x - 2,y),dessinerInvaderSolo(x - 6 ,y), dessinerNewInvader(x - 10, y);

  x = x + jumpEntre ;

  dessinerInvader2(x,y), dessinerNewInvader(x - 2,y) ,dessinerInvaderSolo(x - 6,y),dessinerNewInvader(x - 10, y);
  
  x = x + jumpEntre ;
  
  

  



  if (inverse == 1)
  {

    if (x <= 0 && y == 1)
      {
        x = 14 ;
        y = 0 ;
      }
    
    if (x <= 0 && y == 0)
      {
        x = 14 ;
        y = 1 ;
      }
  }
  
  else
  {

    if (x == 16 && y == 0)
      {
        x = 0;
        y = 1;
      }
      if (x == 16 && y == 1)
      {
        x = 0;
        y = 0;
      }
  }
  
}


