#include <SPI.h>
#include <TFT_ST7735.h>


#define __CS  16  //(D0)
#define __DC  5   //(D1)
#define __RST 4   //(D2)
/*
 SCLK:D5
 MOSI:D7
*/


TFT_ST7735 tft = TFT_ST7735(__CS, __DC, __RST);

void setup() {
  tft.begin();
  tft.print("hello World");
}

void loop(void) {
}