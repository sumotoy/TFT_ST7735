#ifndef _TFT_ST7735_USETT_H_
#define _TFT_ST7735_USETT_H_

/*--------------------------------------------------------------------------------
Here you have to select the display you own..........................
You have a RED PCB, BLACK PCB or what?
Default:__RED_PCB1__ (most common in ebay, RED PCB)
(uncomment just one below...)
----------------------------------------------------------------------------------*/

//#define __BLACK_TAB__
#define __RED_PCB1__
//#define __GREEN_TAB__

/*--------------------------------------------------------------------------------
Teensy LC optional Direct Port vs digitalWriteFast methods
If you have any issues ONLY with Teensy LC and other SPI devices that share
the same SPI lines try to comment the line nelow...
The library default uses Direct Port Manipulation (that it's slight faster)
Default:uncommented
----------------------------------------------------------------------------------*/
#define _TEENSYLC_FASTPORT

/*--------------------------------------------------------------------------------
Default Background Color & default Foreground Color.
When display turns on, it will set the defaul background and foreground.
the default background and foreground affects several other function
when you forget to assign color, for example clearScreen() will clear screen to black
Assigning setBackground(0xF800), red, will result in a red screen when cleared.
Default:0x0000 (black)
----------------------------------------------------------------------------------*/
#define _ST7735_BACKGROUND		BLACK
#define _ST7735_FOREGROUND		WHITE
/*--------------------------------------------------------------------------------
ST7735 max capable SPI SPeed.
Somo module has problems to work at full speed, I don't know exactly why but I have four nodemcu modules
all running at full speed and never a problem. I actually updated all my modules with 
v1.3.0.2 AT Firmware.bin, official one, but I'm not expert on this, maybe it's not important.
You can slow down the speed by changing the default to 8000000.
Default:80000000UL
----------------------------------------------------------------------------------*/
const unsigned long _ST7735_maxSPIspeed = 65000000UL;
/*--------------------------------------------------------------------------------
ESP8266 Compatibility mode.
This force library to use an alternative way to trigger ESP8266 GPIO, if you uncomment
the line it will use the standard digitaWrite wich is slow, this help debuggin.
NOTE: This is slower!
Default:commented
----------------------------------------------------------------------------------*/
//#define _ESP8266_STANDARDMODE

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*---------------------------------------------------------------------------------*/
//								 END OF USER SETTINGS


#if defined(__BLACK_TAB__)
	#define  _TFTWIDTH		128
	#define  _TFTHEIGHT 	160
	#define __COLORSPC		1// 1:GBR - 0:RGB
	#define __COFFSET		0
	#define __ROFFSET		0
#elif defined (__RED_PCB1__)
	#define  _TFTWIDTH		128
	#define  _TFTHEIGHT 	160
	#define __COLORSPC		0// 1:GBR - 0:RGB
	#define __COFFSET		0
	#define __ROFFSET		0
	#define __GAMMASET2
#elif defined (__GREEN_TAB__)
	#define  _TFTWIDTH		128
	#define  _TFTHEIGHT 	160
	#define __COLORSPC		1// 1:GBR - 0:RGB
	#define __COFFSET		2
	#define __ROFFSET		1
	#define __GAMMASET2
#else
	#error You must select at list one display type!
#endif
	#define _GRAMSIZE		_TFTWIDTH * _TFTHEIGHT


	//#define ST7735_NEEDSWAP

/* GAMMA SET DEFINITIONS ----------------------------------------------------------*/
	#if defined(__GAMMASET1)
		const uint8_t pGammaSet[17]= {16,0x02,0x1C,0x07,0x12,0x37,0x32,0x29,0x2D,0x29,0x25,0x2B,0x39,0x00,0x01,0x03,0x10};
		const uint8_t nGammaSet[17]= {16,0x03,0x1D,0x07,0x06,0x2E,0x2C,0x29,0x2D,0x2E,0x2E,0x37,0x3F,0x00,0x00,0x02,0x10};
	#elif defined(__GAMMASET2)
		const uint8_t pGammaSet[17]= {16,0x09,0x16,0x09,0x20,0x21,0x1B,0x13,0x19,0x17,0x15,0x1E,0x2B,0x04,0x05,0x02,0x0E};
		const uint8_t nGammaSet[17]= {16,0x0B,0x14,0x08,0x1E,0x22,0x1D,0x18,0x1E,0x1B,0x1A,0x24,0x2B,0x06,0x06,0x02,0x0F};
	#elif defined(__GAMMASET3)
		const uint8_t pGammaSet[17]= {16,0x09,0x16,0x09,0x20,0x21,0x1B,0x13,0x19,0x17,0x15,0x1E,0x2B,0x04,0x05,0x02,0x0E};
		const uint8_t nGammaSet[17]= {16,0x0B,0x14,0x08,0x1E,0x22,0x1D,0x18,0x1E,0x1B,0x1A,0x24,0x2B,0x06,0x06,0x02,0x0F};
	#endif

#endif
