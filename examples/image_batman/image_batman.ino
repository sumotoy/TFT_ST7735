/*
Batman
CAUTION: This is too big for Arduino UNO or similar
*/

#include <SPI.h>
#include <TFT_ST7735.h>

#include "_images/batman.c"



#define __CS1 	10
#define __DC 	9


TFT_ST7735 tft1 = TFT_ST7735(__CS1, __DC);


uint16_t color;

void setup()
{
	tft1.begin();
	tft1.drawImage(0, 0, &batman);
}

void loop()
{


}
