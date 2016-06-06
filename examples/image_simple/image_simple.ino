#include <SPI.h>
#include <TFT_ST7735.h>

#include "_images/rad1.c"




#define __CS1 	10
#define __DC 	9


TFT_ST7735 tft1 = TFT_ST7735(__CS1, __DC);




void setup()
{
	tft1.begin();
	//drawImage(x,y,&image,OPTIONS,backgroundThreshold);//Options:NONE,TRANSPARENT,REPLACE,BOTH
	tft1.drawImage(30, 0, &rad1);
}

void loop()
{

}
