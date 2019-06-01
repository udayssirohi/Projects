#include <SPI.h>
#include <TinyGPS++.h>
#include <AIR430BoostFCC.h>


#define ADDRESS_LOCAL    0x01

uint8_t check='0';

String ID="$0007018087,$0004887903,$0004886618";

struct sPacket
{ 
  uint8_t from;         
  uint8_t message[1];   
};

struct sPacket rxPacket;

void setup()
{
  Radio.begin(ADDRESS_LOCAL, CHANNEL_1, POWER_MAX);
  
  rxPacket.from = 0;
  memset(rxPacket.message, 0, sizeof(rxPacket.message));
  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.println("Waiting for licence detection");
  
}
// A LOT OF CHANGES ARE STILL NEEDED TO BE MADE TO VOID LOOP...
// what if licence and helmet are both initially detected but the user takes off the helmet while driving 


void loop()
{ 
  while(!dlDetect());
  
  if(helmetDetect()){
    Serial.println("Ignition ON");
  }
    
}

///// HELMET DETECTION //////

int helmetDetect(){
  
  int hval=0;
  
  if (Radio.receiverOn((unsigned char*)&rxPacket, sizeof(rxPacket), 1000) > 0)
  {
    
    if(check!=*rxPacket.message){
    
    if(check=='1'){
    Serial.print(" MSG: ");
    Serial.println("Helmet Detected");
    hval=1;
    }
    else{
    Serial.print(" MSG: ");
    Serial.println("Helmet Removed");
    hval=0;
    }
    
    check=*rxPacket.message;
    }
  }
  
  return hval;
  }


//////// LICENCE DETECTION ////////

int dlDetect(){
  String msg;
  char c;
  int dlval=0; 
  
  
  if(Serial1.available()){
    while(Serial1.available()){
      c=Serial1.read();
      msg+=c;
      delay(10);
      }
      msg=msg.substring(0,11);
      
      if(ID.indexOf(msg)<0){
        Serial.println("Unauthorized Access");
        dlval=0; //no use
        }
      else {dlval=1;
      Serial.println("Licence Detected");
      }
        
  }
  
  return dlval;
  }

/// SMART DELAY (Used for GPS interfacing) ///

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

//// PRINTING FLOAT (Used for GPS)  ///////


static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    Serial.print("Not receiving any data");
    Serial.print(' ');  
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
    Serial.print(' ');
  }
  smartDelay(0);
}

  
