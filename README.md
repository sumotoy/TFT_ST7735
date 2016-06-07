# TFT_ST7735
A brand new version, based on my TFT_ILI9163C, same commands and very fast. Works with Teensy's, Arduino's 8Bit (uno, etc), DUE,ESP8266<br>
Now beta stage, tested with Teensy's and ESP8266, pretty stable<br>
Use the same commands of my TFT_ILI9163C so you can use the same wiki https://github.com/sumotoy/TFT_ILI9163C/wiki<br>

***

<b>Display's Compatible:</b><br>
<b>1.8TFT SPI 128*160 Red PCB</b><br>
Uncomment:<code>#include "../_display/TFT_ST7735_RED_PCB1.h"</code> in settings file<br>
![red1](https://github.com/sumotoy/TFT_ST7735/blob/docs/Images/redpcb1.jpg)<br>
<b>1.44" SPI 128*128 V2.1</b> (similar to ILI9163C but ST7735!)<br>
Uncomment:<code>#include "../_display/TFT_ST7735_RED_PCB_SMALL.h"</code> in settings file<br>
Front<br>
![red2a](https://github.com/sumotoy/TFT_ST7735/blob/docs/Images/small_front.jpg)<br>
Rear<br>
![red2b](https://github.com/sumotoy/TFT_ST7735/blob/docs/Images/small_back.jpg)<br>

<b>FEATURES:</b><br>
- Rocket fast!
- Based on my new TFT_ILI9163C, can share same Icons,Images,Fonts and commands.
- Don't have the SPI speed limitation of the my old library, tested at 168Mhz.
- Uses LPGO Font/Icon Rendering.
- Compatible with many CPU's (see list at the bottom)
- Fully SPI Transaction compatible.
- Fully featured set of commands, it's almost impossible you won't find what you'll need!
- Lot of examples.<br>

<b>About Display and connections:</b><br>
My display it's 1.8" 128*160 buy from ebay, RED pcb and has a SD card (that needssome modification if you want to use with Hi speed SPI or never work!).<br>
My display has 3v3 regulator onboard and works at 5V but signal level are still at 3V3! You are warned! Never connect directly to Arduino or any 5V CPU or you will destroy it! You need a Level Converter chip like CD4050.<br>
The Backlight led need a resistor, I've used a 150R connected to 5V but you need to be sure about yours or you will destroy the backlight and your screen will not be useable so pay EXTRA ATTENTION TO THIS!!!<br>
The RST it's optional, I've connected trough a 10K resistor to +3v3.<br><br>

<b>Connections:</b><br>
Display -> CPU<br>
LED: 150R to 220R (depends of display) connected to VCC<br>
SCK: SPI SCLK<br>
SDA: MOSI<br>
A0: RS<br>
RESET: 10Kohm to +3V3<br>
CS: SS<br>
GND: GND<br>
VCC: If you have a regulator on display connect to 5V<br><br>

<b>CPU's compatible:</b><br>
- Teensy 3.0 (can use also alternative SPI pins!)
- Teensy 3.1 (can use also alternative SPI pins!)
- Teensy 3.2 (can use also alternative SPI pins!)
- Teensy LC (can use also alternative SPI pins!)
- Any arduino 8bit (UNO,etc.)
- DUE
- ESP8266
- SPARK (from next version)<br>

<b>What about SD card holder:</b><br>
I know you will ask so before run to solder and connect it please read this!<br>
On 8 bit AVR you probably can use it but this only because you are running at very low SPI speed. With High speed CPU things are totally different, the chinese vendor always solder resistors or (worst) capacitors on SD card holder SPI lines, this cause problems in the SPI bus and result are unexpected, SD most of the time don't work and cause problems even on display side!<br>
So what?<br>
Buy a trusted high quality SD holder (not from chinese where High Quality it's still an unknown word) and connect very near CPU with smallest cable you can, SD have weak signal!<br>
Do NOT trust SD card holder with level changer chip mounted on (sometime passed as high quality buffers!), these buffers/level converter destroy literally your SPI waveforms and cause many problems on SPI bus, they are designed for slow AVR<br>
The best SD holder has no resitors, capacitor (ok, just one on supply it's ok) or whatever.<br>
Use always REAL branded SD cards and high speed ones (level 10 and up).<br>
It's possible modify the SD holder mounted on display? Probably yes, have to try, maybe I will write a wiki about it one day<br>
