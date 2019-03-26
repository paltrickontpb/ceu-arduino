#include<LiquidCrystal.h>

volatile int mode = 0;
volatile int val = 1;
volatile char tds[] = "TDS";

LiquidCrystal lcd(12,11,7, 6, 5, 4);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Random Dice");
  lcd.setCursor(0,1);
  lcd.print("Machine");
  attachInterrupt(digitalPinToInterrupt(2), throwDice, RISING);
  attachInterrupt(digitalPinToInterrupt(3), changeMode, RISING);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Mode : ");
  lcd.print(mode);
  delay(10);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Mode : ");
  lcd.print(mode);
  delay(10);
}



void throwDice(){
  switch(mode){
    case 0:
      val = random(1, 7);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(val);
      delay(50);
      break;
    case 1:
      val = random(1, 7);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(val);
      lcd.print(',');
      val = random(1, 7);
      lcd.print(val);
      delay(50);
      break;
    case 2:
      val = random(3);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(tds[val]);
      delay(50);
      break;
  }
}

void changeMode(){
  if (mode == 2)
    mode = 0;
  else
    mode += 1;
}

