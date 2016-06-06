#include <SPI.h>
#include <TFT_ST7735.h>

#include "_images/wifi2s.c"
#include "_images/wifi2sr.c"


#define __CS1 	10
#define __DC 	9


TFT_ST7735 tft1 = TFT_ST7735(__CS1, __DC);




void setup()
{
	tft1.begin();
	tft1.setRotation(2);

}

void loop()
{
	tft1.drawImage(0, 0, &wifi2sr);
	delay(1000);
	tft1.drawImage(0, 0, &wifi2s);
	delay(1000);
}
