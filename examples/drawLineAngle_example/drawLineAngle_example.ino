/*
Draw Line Angle Example
Library has a nice function called drawLineAngle
that let you draw easily needle gauges at any angle
*/

#include <SPI.h>
#include <TFT_ST7735.h>

#define __CS1 	10
#define __DC 	9


TFT_ST7735 tft = TFT_ST7735(__CS1, __DC);


void setup() {

  tft.begin();
  tft.drawCircle(64, 64, 60, 0xFFFF);//draw round gauge
  tft.drawCircle(64, 64, 59, 0xFFFF);//draw round gauge
}

void loop() {
  for (int i = 0; i <= 360; i++) {
    if (i > 0) tft.drawLineAngle(64, 64, i - 1, 58, 0x0000);//erase previous needle
    tft.drawLineAngle(64, 64, i, 58, GREEN);//draw needle
    delay(10);
  }
}

