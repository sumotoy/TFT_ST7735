#include <SPI.h>
#include <TFT_ST7735.h>

//#include "fonts/fluide_caps.c"


// Color definitions
#define RED     0xF800

/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
 14.676
 */
#define __CS  10
#define __DC  6
#define __RST 23
/*
Teensy 3.x can use: 2,6,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/


TFT_ST7735 tft = TFT_ST7735(__CS, __DC, __RST);

void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  tft.begin();
  tft.drawLine(0,0,tft.width(),tft.height(),RED);
  tft.drawLine(tft.width(),0,0,tft.height(),RED);
  //tft.setFont(&fluide_caps);
  tft.setTextSize(2);
  tft.setCursor(tft.width()/2,tft.height()/2,true);//<- an optional parameter will center text!
  tft.print("ABCD");

}

void loop(void) {
}