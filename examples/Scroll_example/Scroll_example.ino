/*
Undocumented scroll!
Accordly version 1.9 of the official ST7735 datasheet the chip it's not scrolling
capable but I incidentally fould that's not true, here's an example.
Since it's an undocumented/unsupported feature the scrolling routine it's still
not working well as it should but I'm positive to fix this soon.
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


TFT_ST7735 tft = TFT_ST7735(__CS, __DC, __RST);

void setup() {
  tft.begin();
  tft.setRotation(0);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.println(0xDEAD, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.println("Hello");

  tft.defineScrollArea(23, 50);
  //try load again with this commented out!
}


int t = 0;


void loop(void) {
  tft.scroll(t);
  if (t >= tft.height()-22) {
    t = 0;
  }
  else {
    t++;
  }

  delay(10);
}


void testFilledRects() {
  int           n, i, i2,
                cx = (tft.width()  / 2),
                cy = (tft.height() / 2);
  n = min(tft.width(), tft.height());
  for (i = n; i > 0; i -= 6) {
    i2    = i / 2;
    tft.fillRect(cx - i2, cy - i2, i, i, random(0x0000, 0xFFFF));
    tft.drawRect(cx - i2, cy - i2, i, i, random(0x0000, 0xFFFF));
  }
}