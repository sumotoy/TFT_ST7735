#ifndef _TFT_ST7735_USETT_H_
#define _TFT_ST7735_USETT_H_
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
									USER SETTINGS
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/	
/*--------------------------------------------------------------------------------
Select your display here
What display you have?
Default: #include "../_display/TFT_ST7735_RED_PCB1.h"
(uncomment just one below...)
----------------------------------------------------------------------------------*/
#if !defined (TFT_ST7735_INSTANCES)
	//#include "../_display/TFT_ST7735_RED_PCB1.h"
	#include "../_display/TFT_ST7735_RED_PCB_SMALL.h"
	//more to come
#endif
/*--------------------------------------------------------------------------------
- Size Reducing (decrease slight performances) -
Ignored for Teensy 3.x, DUE
Small CPU like UNO have very small resources and code optimizations uses lot of.
Uncomment _ST7735_SIZEOPTIMIZER will decrease space needed by code but some performance
will suffer a bit, however it can be usefult in many cases!
Default:uncommented (automatically enabled for some CPU)
----------------------------------------------------------------------------------*/
#if !defined(__MK20DX128__) && !defined(__MK20DX256__) && !defined(__SAM3X8E__)// && !defined(ESP8266)
#define _ST7735_SIZEOPTIMIZER			
#endif		
/*--------------------------------------------------------------------------------
- Default Display Rotation -
This parameter can be changed in your code but here you can force orientation
Default:0
----------------------------------------------------------------------------------*/
#define _ST7735_ROTATION			0
/*--------------------------------------------------------------------------------
- Default Font -
From version 1.0p7 user can choose here witch font to use as default and even avoid any font.
To change default font, you must:
	_ST7735_DEF_FONT_PATH "the complete path of the font" (default:"_fonts/defaultFont.c")
	_ST7735_DEF_FONT_NAME	the_unique_name_of_the_font (default:defaultFont)
To avoid any font, just uncomment the 2 defines and a blank font will be loaded (almost 0 resources)
Default: (defaultFont = arial_2x)
#define _ST7735_DEF_FONT_PATH			"_fonts/defaultFont.c"
#define _ST7735_DEF_FONT_NAME			defaultFont
----------------------------------------------------------------------------------*/
#define _ST7735_DEF_FONT_PATH			"_fonts/defaultFont.c"
#define _ST7735_DEF_FONT_NAME			defaultFont
/*--------------------------------------------------------------------------------
- Default Background Color & Default Foreground Color -
When display turns on, it will set the defaul background and foreground.
the default background and foreground affects several other function
when you forget to assign color, for example clearScreen() will clear screen to black
Assigning setBackground(0xF800), red, will result in a red screen when cleared.
Default:BLACK & WHITE
----------------------------------------------------------------------------------*/
#define _ST7735_BACKGROUND		BLACK
#define _ST7735_FOREGROUND		WHITE
/*--------------------------------------------------------------------------------
- Teensy LC Fast CS Port option -
Teensy LC optional Direct Port vs digitalWriteFast methods
If you have any issues ONLY with Teensy LC and other SPI devices that share
the same SPI lines try to comment the line nelow...
The library default uses Direct Port Manipulation (that it's slight faster)
Default:uncommented
----------------------------------------------------------------------------------*/
#if defined(__MKL26Z64__)
	#define _TEENSYLC_FASTPORT	
#endif
/*--------------------------------------------------------------------------------
- ESP8266 Faster SPI -
This force library to use the SPI.write method instead the legacy SPI.transfer.
As result is much faster. (Thanks Reaper7)
Default:uncommented
----------------------------------------------------------------------------------*/
#if defined(ESP8266)
	#define _ESP8266_SPIFAST	
#endif
/*--------------------------------------------------------------------------------
- ESP8266 Compatibility mode -
This force library to use an alternative way to trigger ESP8266 GPIO, if you uncomment
the line it will use the standard digitaWrite wich is slow, this help debugging.
NOTE: uncomment this, code is MUCH slower!
Default:commented
----------------------------------------------------------------------------------*/
#if defined(ESP8266)
	//#define _ESP8266_STANDARDMODE	
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*---------------------------------------------------------------------------------
 							 END OF USER SETTINGS
----------------------------------------------------------------------------------*/

/* GAMMA SET DEFINITIONS ----------------------------------------------------------*/

	#if (TFT_ST7735_GAMMASET == 1)
		static const uint8_t pGammaSet[15]= {0x0F,0x31,0x2B,0x0C,0x0E,0x08,0x4E,0xF1,0x37,0x07,0x10,0x03,0x0E,0x09,0x00};
		static const uint8_t nGammaSet[15]= {0x00,0x0E,0x14,0x07,0x11,0x07,0x31,0xC1,0x48,0x08,0x0F,0x0C,0x31,0x36,0x0F};
	#elif (TFT_ST7735_GAMMASET == 2)
		static const uint8_t pGammaSet[15]= {0x3F,0x21,0x12,0x22,0x1C,0x15,0x42,0xB7,0x2F,0x13,0x02,0x0A,0x01,0x00,0x00};
		static const uint8_t nGammaSet[15]= {0x09,0x18,0x2D,0x0D,0x13,0x15,0x40,0x48,0x53,0x0C,0x1D,0x25,0x2E,0x24,0x29};
	#elif (TFT_ST7735_GAMMASET == 3)
		static const uint8_t pGammaSet[15]= {0x3F,0x26,0x23,0x30,0x28,0x10,0x55,0xB7,0x40,0x19,0x10,0x1E,0x02,0x01,0x00};
		static const uint8_t nGammaSet[15]= {0x09,0x18,0x2D,0x0D,0x13,0x15,0x40,0x48,0x53,0x0C,0x1D,0x25,0x2E,0x24,0x29};
	#elif (TFT_ST7735_GAMMASET == 4)
		static const uint8_t pGammaSet[15]= {0x3F,0x25,0x1C,0x1E,0x20,0x12,0x2A,0x90,0x24,0x11,0x00,0x00,0x00,0x00,0x00};
		static const uint8_t nGammaSet[15]= {0x20,0x20,0x20,0x20,0x05,0x15,0x00,0xA7,0x3D,0x18,0x25,0x2A,0x2B,0x2B,0x3A};
	#endif


/*---------------------------------------------------------------------------------*/

#endif
