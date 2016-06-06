#include <SPI.h>
#include <TFT_ST7735.h>

#include "_icons/wifi.c"




#define __CS1 	10
#define __DC 	9

TFT_ST7735 tft1 = TFT_ST7735(__CS1, __DC);




void setup()
{
	tft1.begin();
	//drawIcon(x,y,&icon,scale,foreground,background,inverse);
	tft1.drawIcon(0, 0, &wifi,1,WHITE,BLACK,1);
}

void loop()
{

}
