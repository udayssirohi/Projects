#include <LiquidCrystal.h>
#define RELAY1 6
#define RELAY2 7

/*
PINS IN USE:

DIGITAL-2,3,4,5,6,7,11,12,13
ANALOG-

*/

int val=0;
int check=0;
const int PIR=13;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void lcd_display(int ch){
    lcd.display();
    lcd.setCursor(0,0);
    if (ch==0){  
    lcd.print("WELCOME MASTER!");
    lcd.setCursor(0,1);
    delay(2000);
    lcd.print("ON");
    delay(5000);
    }
    else{  
    lcd.print("BYE BYE!");
    lcd.setCursor(0,1);
    lcd.print("OFF");
    delay(2000); 
    }   
    lcd.noDisplay();
  
  }

void setup()
{
  pinMode(PIR,INPUT);
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  lcd.begin(16,2);
  }

void loop(){
  val=digitalRead(PIR);
  if (val==HIGH){
    if (check==0){
      // GOING IN
    lcd_display(0);
    digitalWrite(RELAY1,LOW);
    delay(1000);  
    digitalWrite(RELAY2,LOW);


    check=1;
    }
    else{
      // GOING OUT
    lcd_display(1);
    digitalWrite(RELAY1,HIGH);
    delay(1000);
    digitalWrite(RELAY2,HIGH);

    
    check=0;
        }  
    }
  
  }  
  
