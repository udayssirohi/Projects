#include<string.h>

#define IN 13
int var=0;

char checkChar[6];
char Char[38];
char binChar[1][6]={100001};

void setup() {
Serial.begin(9600);  
pinMode(IN,INPUT);
}

void loop() {
  float timer0=0;
     
  for (int ch=0;ch<6;ch++){  
    
  while(var!=HIGH){var=digitalRead(IN);}
  
  timer0=counter();
  Serial.print(timer0);
  Serial.println(" s");
  
  tapCheck(timer0,ch);                       
  var=LOW;  
} 
 
  matchMorse();

  }

 
float counter(){
  float x=0;
  while(digitalRead(IN)==HIGH){
    delay(1);
    x++;
    }    
  return x/1000;
  }
  
void tapCheck(float t0,int getch){
  int check;
  check=int(t0);
  
  if (check>=1 && check<<2) {
  checkChar[getch]='1';
  }
  else {
  checkChar[getch]='0';
  }
  
  Serial.println(checkChar);
  
  }
  
void matchMorse(){
  Serial.println("Started matching");
  int c;
  
  for(int i=0; i<sizeof(binChar);i++){ 
 
  c=strcmp(checkChar,binChar[i]);
  
  if (c==0)
  { Serial.println("MATCH");
  break; }
  }
  
  if(c!=0) Serial.println("No Match");
  strcpy(checkChar,"");
  
}
