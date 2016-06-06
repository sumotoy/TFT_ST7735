/*
Icons are flexible! Here's a negative image colored as positive
*/

#include <SPI.h>
#include <TFT_ST7735.h>

#include "_icons/mixer1.c"


#define __CS1 	10
#define __DC 	9


TFT_ST7735 tft1 = TFT_ST7735(__CS1, __DC);


void setup()
{
	tft1.begin();
	tft1.setRotation(0);
}

void loop()
{
	uint16_t color = random(0x00FF, 0xFFFF);
	tft1.drawIcon(0, 0, &mixer1, 1, color, color, true);
	delay(50);
}