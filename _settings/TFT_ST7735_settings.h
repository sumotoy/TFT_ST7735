#ifndef _TFT_ST7735_USETT_H_
#define _TFT_ST7735_USETT_H_

/*--------------------------------------------------------------------------------
Here you have to select the display you own..........................
You have a RED PCB, BLACK PCB or what?
(uncomment just one below...)
Default:__144_RED_PCB__
----------------------------------------------------------------------------------*/

//#define __BLACK_TAB__
#define __RED_PCB1__	//popular chinese 
//#define __GREEN_TAB__

/*--------------------------------------------------------------------------------
Since some CPU has limited RAM, you can force fonts to avoid use it.
Teensy 3.0, Teensy 3.1 has not real PROGMEM support so it's automatically disabled.
----------------------------------------------------------------------------------*/
#define _FORCE_PROGMEM__

/*--------------------------------------------------------------------------------
Teensy LC optional Direct Port vs digitalWriteFast methods
If you have any issues ONLY with Teensy LC and other SPI devices that share
the same SPI lines try to comment the line nelow...
The library default uses Direct Port Manipulation (that it's slight faster)
Default:uncommented
----------------------------------------------------------------------------------*/
#define _TEENSYLC_FASTPORT

/*--------------------------------------------------------------------------------
Teesny 3.0 and Teensy 3.1 force compatibility issue flag.
The following option will force SPI to acknoledge for trasmitted data.
This will slow down the SPI speed a bit but can be helpful if you have other devices
that uses very high SPI speed that share the same SPI lines of your display.
If you have troubles, try to uncomment the following line, but REMEMBER tha it will
slow down speed!
Default:commented
----------------------------------------------------------------------------------*/
//#define __FORCECOMPAT_SPI

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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*---------------------------------------------------------------------------------*/
//								 END OF USER SETTINGS
/*---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*/
//								   DISPLAY PRESET
/*---------------------------------------------------------------------------------*/
#if defined(__BLACK_TAB__)
	const uint8_t _ST7735_TFTWIDTH 	  = 128;
	const uint8_t _ST7735_TFTHEIGHT   = 160;
	const uint8_t _ST7735_COFFSET 	  = 0;
	const uint8_t _ST7735_ROFFSET 	  = 0;
	const uint8_t __COLORSPC 		  = 1;// 1:GBR - 0:RGB
	//#define __GAMMASET3
	const uint8_t _ST7735_FRMCTR1P[4] = {3,0x00,0x06,0x03};
	const uint8_t _ST7735_FRMCTR2P[1] = {0};
	const uint8_t _ST7735_FRMCTR3P[1] = {0};
	const uint8_t _ST7735_PIXFMT[2]   = {1,0x05};
	const uint8_t _ST7735_MADCTL[2]   = {1,0xC0};
	const uint8_t _ST7735_DFUNCTR[3]  = {2,0x15,0x02};
	const uint8_t _ST7735_INVCTR[2]   = {1,0x00};
	const uint8_t _ST7735_PWCTR1[3]   = {2,0x02,0x70};
	const uint8_t _ST7735_PWCTR2[2]   = {1,0x05};
	const uint8_t _ST7735_PWCTR3[3]   = {2,0x01,0x02};
	const uint8_t _ST7735_PWCTR4[1]   = {0};
	const uint8_t _ST7735_PWCTR5[1]   = {0};
	const uint8_t _ST7735_PWCTR6[3]   = {2,0x11,0x15};
	const uint8_t _ST7735_VMCTR1[3]   = {2,0x3C,0x38};
	const uint8_t _ST7735_CASET[5]    = {4,0x00,0x02,0x00,0x81};
	const uint8_t _ST7735_RASET[5]    = {4,0x00,0x02,0x00,0x81};
#elif defined (__RED_PCB1__)
	const uint8_t _ST7735_TFTWIDTH 	  = 128;
	const uint8_t _ST7735_TFTHEIGHT   = 160;
	const uint8_t _ST7735_COFFSET 	  = 0;
	const uint8_t _ST7735_ROFFSET 	  = 0;
	const uint8_t __COLORSPC 		  = 0;// 1:GBR - 0:RGB
	#define __GAMMASET2		
	const uint8_t _ST7735_FRMCTR1P[4] = {3,0x01,0x2C,0x2D};//ok
	const uint8_t _ST7735_FRMCTR2P[4] = {3,0x01,0x2C,0x2D};//ok
	const uint8_t _ST7735_FRMCTR3P[7] = {6,0x01,0x2C,0x2D,0x01,0x2C,0x2D};//ok
	const uint8_t _ST7735_PIXFMT[2]   = {1,0x05};//0x05(16bit) - 0x06(18bit)
	const uint8_t _ST7735_MADCTL[2]   = {1,0xC8};
	const uint8_t _ST7735_DFUNCTR[1]  = {0};
	const uint8_t _ST7735_INVCTR[2]   = {1,0x07};
	const uint8_t _ST7735_PWCTR1[4]   = {3,0xA2,0x02,0x84};
	const uint8_t _ST7735_PWCTR2[2]   = {1,0xC5};
	const uint8_t _ST7735_PWCTR3[3]   = {2,0x0A,0x00};
	const uint8_t _ST7735_PWCTR4[3]   = {2,0x8A,0x2A};
	const uint8_t _ST7735_PWCTR5[3]   = {0,0x8A,0xEE};
	const uint8_t _ST7735_PWCTR6[1]   = {0};
	const uint8_t _ST7735_VMCTR1[2]   = {1,0x0E};
	const uint8_t _ST7735_CASET[5]    = {4,0x00,0x00,0x00,0x7F};
	const uint8_t _ST7735_RASET[5]    = {4,0x00,0x00,0x00,0x9F};
#elif defined (__GREEN_TAB__)
	const uint8_t _ST7735_TFTWIDTH 	  = 128;
	const uint8_t _ST7735_TFTHEIGHT   = 160;
	const uint8_t _ST7735_COFFSET 	  = 2;
	const uint8_t _ST7735_ROFFSET 	  = 1;
	const uint8_t __COLORSPC 		  = 1;// 1:GBR - 0:RGB
	#define __GAMMASET2		
	const uint8_t _ST7735_FRMCTR1P[4] = {3,0x01,0x2C,0x2D};
	const uint8_t _ST7735_FRMCTR2P[4] = {3,0x01,0x2C,0x2D};
	const uint8_t _ST7735_FRMCTR3P[7] = {6,0x01,0x2C,0x2D,0x01,0x2C,0x2D};
	const uint8_t _ST7735_PIXFMT[2]   = {1,0x05};
	const uint8_t _ST7735_MADCTL[2]   = {1,0xC8};
	const uint8_t _ST7735_DFUNCTR[1]  = {0};
	const uint8_t _ST7735_INVCTR[2]   = {1,0x07};
	const uint8_t _ST7735_PWCTR1[4]   = {3,0xA2,0x02,0x84};
	const uint8_t _ST7735_PWCTR2[2]   = {1,0xC5};
	const uint8_t _ST7735_PWCTR3[3]   = {2,0x0A,0x00};
	const uint8_t _ST7735_PWCTR4[3]   = {2,0x8A,0x2A};
	const uint8_t _ST7735_PWCTR5[3]   = {0,0x8A,0xEE};
	const uint8_t _ST7735_PWCTR6[1]   = {0};
	const uint8_t _ST7735_VMCTR1[2]   = {1,0x0E};
	const uint8_t _ST7735_CASET[5]    = {4,0x00,0x02,0x00,0x7F+0x02};
	const uint8_t _ST7735_RASET[5]    = {4,0x00,0x01,0x00,0x9F+0x01};
#else
	#error You must select at list one display type!
#endif
	static const uint16_t _GRAMSIZE = _ST7735_TFTWIDTH * _ST7735_TFTHEIGHT;
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

#if defined(__AVR__)
	#if !defined(_FORCE_PROGMEM__)
		#define _FORCE_PROGMEM__
	#endif
#elif defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
	#if defined(_FORCE_PROGMEM__)
		#undef _FORCE_PROGMEM__
	#endif
#endif

#endif
