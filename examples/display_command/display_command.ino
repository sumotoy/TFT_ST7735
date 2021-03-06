/*
Turn display ON/OFF - this command it's almost unusable since it doesn't control the backligh
It result in a white screen!
*/


#include <SPI.h>
#include <TFT_ST7735.h>

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

/*
Teensy3.x and Arduino's
 You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
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


TFT_ST7735 tft = TFT_ST7735(__CS, __DC,__RST);

void setup() {
  tft.begin();
  tft.fillScreen(0xF81F);
  tft.print("Hello World!");
}

void loop(void) {
  tft.display(false);
  delay(1000);
  tft.display(true);
  delay(1000);
}