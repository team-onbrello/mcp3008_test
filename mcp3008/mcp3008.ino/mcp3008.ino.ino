/***************************************************
Simple example of reading the MCP3008 analog input channels and printing
them all out.

Author: Carter Nelson
License: Public Domain
****************************************************/

#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc[2];

int count = 0;

void setup() {
  Serial.begin(230400);
  while (!Serial);

  Serial.println("MCP3008 simple test.");

  // Hardware SPI (specify CS, use any available digital)
  // Can use defaults if available, ex: UNO (SS=10) or Huzzah (SS=15)
  adc[0].begin(9);
  adc[1].begin(10);
  // Feather 32u4 (SS=17) or M0 (SS=16), defaults SS not broken out, must specify
  //adc.begin(10);  

  // Software SPI (specify all, use any available digital)
  // (sck, mosi, miso, cs);
  //adc.begin(13, 11, 12, 10);
}

String strPad2(int num,int zeroCount){
  char tmp[256];
  char param[5] = {'%','0',(char)(zeroCount+48),'d','\0'};
  sprintf(tmp,param,num);
  return tmp;
}

int res[16];
unsigned long t0=0;
unsigned long t1=0;
char buf[6];
void loop() {
  t0 = micros();
  while (1) {
    for (int ad=0; ad<2; ad++){
      for (int ch=0; ch<8; ch++) {
        sprintf(buf,"%04d\0",adc[ad].readADC(ch));
        Serial.print(buf);
        Serial.print(", ");
      }
    }\
    t1 = micros();
    Serial.print(t1-t0);
    t0=t1;
    Serial.println(); 
  }
}
