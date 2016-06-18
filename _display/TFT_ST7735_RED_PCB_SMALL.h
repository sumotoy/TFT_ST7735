#ifndef _TFT_ST7735_REDPCBSMALL_H
#define _TFT_ST7735_REDPCBSMALL_H
#include <stdio.h>
/*=========================================================================================
	Part of TFT_ST7735 library
    Copyright (c) 2014/2015/2016, .S.U.M.O.T.O.Y., coded by Max MC Costa.

    TFT_ST7735 Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TFT_ST7735 Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
	---------------------------------------------------------------------------------------
	Display Type: RED PCB small 1.44" SPI 128*128 V2.1
	This is really similar to ILI9163 ones but use an ST7735 controller!
	https://github.com/sumotoy/TFT_ST7735/blob/docs/Images/small_front.jpg
	https://github.com/sumotoy/TFT_ST7735/blob/docs/Images/small_back.jpg
===========================================================================================*/
	/* Physical display size
	*/
	static const int16_t	TFT_ST7735_TFTWIDTH		=	128;
	static const int16_t	TFT_ST7735_TFTHEIGHT 	=	128;
	static const uint32_t	TFT_ST7735_CGRAM		=	TFT_ST7735_TFTWIDTH * TFT_ST7735_TFTHEIGHT;
	/* Gamma Set
	I have included several pre-computed gamma set, you can try any between: 1..4
	setting to 5 will disable completely gamma set. */
	#define TFT_ST7735_GAMMASET	1
	/* Colorspace
	Some display can use GBR colorspace or RGB (1:GBR - 0:RGB) */
	static const boolean	TFT_ST7735_CSPACE 		= 	1;// 1:GBR - 0:RGB
	/* Offset
	Vendors like to set his display as they like, result in offset that is different between models
	Here's a offset map for any rotatio of the display, helping code to deal with this.
	First index is rotation, second 2 parameters are offset in x and y axis. [rotation][x,y] */
	
	static const uint8_t 	TFT_ST7735_OFST[4][2] = {
		{0,0},//rot 0 - x,y
		{0,0},//rot 1 - x,y
		{0,32},//rot 2 - x,y
		{32,0} //rot 3 - x,y
	};
	
	/*Defines how many bits per pixel are used in the interface*/
	static const uint8_t 	TFT_ST7735_PIXFMT		=	0x05;
	/*Selects the gamma curve used by the display device (0x01[1],0x02[2],0x04[3],0x08[4])*/
	static const uint8_t 	TFT_ST7735_GAMMACURV 	=	0x01;//[alt 0x04] default gamma curve
	//Frame Rate Control_1 (In normal mode/Full colors)
	static const uint8_t 	TFT_ST7735_FRMCTR1[3]	=	{0x00,0x06,0x03};//0x00,0x06,0x03 - 0x01,0x2C,0x2D
	//Frame Rate Control_2 (Idle mode/8 Bits)
	static const uint8_t 	TFT_ST7735_FRMCTR2[3]	=	{0x01,0x2C,0x2D};
	//Frame Rate Control_3 ()
	static const uint8_t 	TFT_ST7735_FRMCTR3[3]	=	{0x01,0x2C,0x2D};
	//
	static const uint8_t	TFT_ST7735_DINVCTR		=	0x00;//(0x00 or 0x07)
	//Power settings
	/* Set the GVDD and voltage*/
	static const uint8_t 	TFT_ST7735_PWCTR1[3]	= {0xA2,0x02,0x84};
	static const uint8_t 	TFT_ST7735_PWCTR2		= 0xC5;
	/*Set the amount of current in Operation amplifier in normal mode/full colors.*/
	static const uint8_t 	TFT_ST7735_PWCTR3[2]	= {0x0A,0x00};
	/*Set the amount of current in Operational amplifier in Idle mode/8-colors*/
	static const uint8_t 	TFT_ST7735_PWCTR4[2]	= {0x8A,0x2A};
	/*Set the amount of current in Operational amplifier in Partial mode/full-colors*/
	static const uint8_t 	TFT_ST7735_PWCTR5[2]	= {0x8A,0x2A};
	/*Set VCOMH Voltage*/
	static const uint8_t 	TFT_ST7735_VCOMCTR1[2] =	{0x3C,0x38};
#endif