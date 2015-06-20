#include "TFT_ST7735.h"

// #ifdef __AVR__
	// #include <avr/pgmspace.h>
// #elif defined(ESP8266)

// #elif defined(__SAM3X8E__)
	// #include <include/pio.h>
	// #define PROGMEM
	// #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
	// #define pgm_read_word(addr) (*(const unsigned short *)(addr))
	// typedef unsigned char prog_uchar;
// #endif
	
//constructors

//Teensy 3.0, Teensy 3.1
#if defined(__MK20DX128__) || defined(__MK20DX256__)
	TFT_ST7735::TFT_ST7735(uint8_t cspin,uint8_t dcpin,uint8_t rstpin,uint8_t mosi,uint8_t sclk)
	{
		_cs   = cspin;
		_rs   = dcpin;
		_rst  = rstpin;
		_mosi = mosi;
		_sclk = sclk;
	}
//Teensy LC
#elif defined(__MKL26Z64__)
	TFT_ST7735::TFT_ST7735(uint8_t cspin,uint8_t dcpin,uint8_t rstpin,uint8_t mosi,uint8_t sclk)
	{
		_cs   = cspin;
		_rs   = dcpin;
		_rst  = rstpin;
		_mosi = mosi;
		_sclk = sclk;
		_useSPI1 = false;
		if ((_mosi == 0 || _mosi == 21) && (_sclk == 20)) _useSPI1 = true;
	}
//Arduino's and unknown CPU
#else
	TFT_ST7735::TFT_ST7735(uint8_t cspin,uint8_t dcpin,uint8_t rstpin)
	{
		_cs   = cspin;
		_rs   = dcpin;
		_rst  = rstpin;
	}
#endif


void TFT_ST7735::useBacklight(const uint8_t pin)
{
	_bklPin = pin;
	pinMode(_bklPin, OUTPUT);
	digitalWrite(_bklPin,LOW);
}

//Arduino Uno, Leonardo, Mega, Teensy 2.0, etc
#if defined(__AVR__)
	void TFT_ST7735::writecommand(uint8_t c)
	{
		startTransaction();
			enableCommandStream(); spiwrite(c);
		endTransaction();
	}

	void TFT_ST7735::writedata(uint8_t c)
	{
		startTransaction();
			enableDataStream(); spiwrite(c);
		endTransaction();
	} 

	void TFT_ST7735::writedata16(uint16_t d)
	{
		startTransaction();
			enableDataStream(); spiwrite16(d);
		endTransaction();
	} 

	void TFT_ST7735::setBitrate(uint32_t n)
	{
		#if !defined (SPI_HAS_TRANSACTION)
			if (n >= 8000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV2);
			} else if (n >= 4000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV4);
			} else if (n >= 2000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV8);
			} else {
				SPI.setClockDivider(SPI_CLOCK_DIV16);
			}
		#endif
	}
#elif defined(__SAM3X8E__)// Arduino Due

	void TFT_ST7735::writecommand(uint8_t c)
	{
		startTransaction();
			enableCommandStream(); spiwrite(c);
		endTransaction();
	}

	void TFT_ST7735::writedata(uint8_t c)
	{
		startTransaction();
			enableDataStream(); spiwrite(c);
		endTransaction();
	} 

	void TFT_ST7735::writedata16(uint16_t d)
	{
		startTransaction();
			enableDataStream(); spiwrite16(d);
		endTransaction();
	}


	void TFT_ST7735::setBitrate(uint32_t n)
	{
		#if !defined(SPI_HAS_TRANSACTION)
			uint32_t divider = 1;
			while (divider < 255) {
				if (n >= 84000000 / divider) break;
				divider = divider - 1;
			}
			SPI.setClockDivider(divider);
		#endif
	}
#elif defined(__MKL26Z64__)//Teensy LC

	void TFT_ST7735::writecommand(uint8_t c)
	{
		startTransaction();
			enableCommandStream(); spiwrite(c);
		endTransaction();
	}

	void TFT_ST7735::writedata(uint8_t c)
	{
		startTransaction();
			enableDataStream(); spiwrite(c);
		endTransaction();
	} 
	

	void TFT_ST7735::writedata16(uint16_t d)
	{
		startTransaction();
			enableDataStream(); spiwrite16(d);
		endTransaction();
	} 
	


	void TFT_ST7735::setBitrate(uint32_t n)
	{
		//nop
	}
#elif defined(__MK20DX128__) || defined(__MK20DX256__)//Teensy 3.0 & 3.1 

	void TFT_ST7735::setBitrate(uint32_t n)
	{
		//nop
	}
#else

	void TFT_ST7735::writecommand(uint8_t c)
	{
		startTransaction();
			enableCommandStream(); spiwrite(c);
		endTransaction();
	}

	void TFT_ST7735::writedata(uint8_t c)
	{
		startTransaction();
			enableDataStream(); spiwrite(c);
		endTransaction();
	} 

	void TFT_ST7735::writedata16(uint16_t d)
	{
		startTransaction();
			enableDataStream(); spiwrite16(d);
		endTransaction();
	} 

	void TFT_ST7735::setBitrate(uint32_t n)
	{
		#if !defined (SPI_HAS_TRANSACTION)
			if (n >= 8000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV2);
			} else if (n >= 4000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV4);
			} else if (n >= 2000000) {
				SPI.setClockDivider(SPI_CLOCK_DIV8);
			} else {
				SPI.setClockDivider(SPI_CLOCK_DIV16);
			}
		#endif
	}
#endif


void TFT_ST7735::begin(void) 
{
	sleep = 0;
	_portrait = false;
	_initError = 0b00000000;
	_width    = _ST7735_TFTWIDTH;
	_height   = _ST7735_TFTHEIGHT;
	_rotation  = 0;
	_cursor_y  = _cursor_x    = 0;
	_fontScaling  = 1;
	_spaceWidth = 0;
	_interline = 0;
	_centerText = false;
	_defaultBackground = _ST7735_BACKGROUND;
	_defaultForeground = _ST7735_FOREGROUND;
	_textcolor = _textbgcolor = _defaultForeground;
	wrap      = true;
	setFont(&internal);
	_arcAngleMax = 360;
	_arcAngleOffset = -90;
	_bklPin = 255;
#if defined(__AVR__)
	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	csport    = portOutputRegister(digitalPinToPort(_cs));
	rsport    = portOutputRegister(digitalPinToPort(_rs));
	cspinmask = digitalPinToBitMask(_cs);
	rspinmask = digitalPinToBitMask(_rs);
    SPI.begin();
	#if !defined(SPI_HAS_TRANSACTION)
		SPI.setClockDivider(SPI_CLOCK_DIV2); // 8 MHz
		SPI.setBitOrder(MSBFIRST);
		SPI.setDataMode(SPI_MODE0);
	#else
		ST7735_SPI = SPISettings(8000000, MSBFIRST, SPI_MODE0);
	#endif
	*csport |= cspinmask;//hi
	enableDataStream();
#elif defined(__SAM3X8E__)
	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	csport    = digitalPinToPort(_cs);
	rsport    = digitalPinToPort(_rs);
	cspinmask = digitalPinToBitMask(_cs);
	rspinmask = digitalPinToBitMask(_rs);
    SPI.begin();
	#if !defined(SPI_HAS_TRANSACTION)
		SPI.setClockDivider(5); // 8 MHz
		SPI.setBitOrder(MSBFIRST);
		SPI.setDataMode(SPI_MODE0);
	#else
		ST7735_SPI = SPISettings(24000000, MSBFIRST, SPI_MODE0);
	#endif
	csport->PIO_SODR  |=  cspinmask;//HI
	enableDataStream();
#elif defined(__MKL26Z64__)//Teensy LC (preliminary)
	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	if (_useSPI1){
		if ((_mosi == 0 || _mosi == 21) && (_sclk == 20)) {//identify alternate SPI channel 1 (24Mhz)
			ST7735_SPI = SPISettings(24000000, MSBFIRST, SPI_MODE0);
			SPI1.setMOSI(_mosi);
			SPI1.setSCK(_sclk);
			SPI1.begin();
			_useSPI1 = true; //confirm
		} else {
			bitSet(_initError,0);
			return;
		}
		if (!SPI.pinIsChipSelect(_cs)) {//ERROR
			bitSet(_initError,1);
			return;
		}
	} else {
		if ((_mosi == 11 || _mosi == 7) && (_sclk == 13 || _sclk == 14)) {//valid SPI pins?
			ST7735_SPI = SPISettings(12000000, MSBFIRST, SPI_MODE0);
			SPI.setMOSI(_mosi);
			SPI.setSCK(_sclk);
			SPI.begin();
			_useSPI1 = false; //confirm
		} else {
			bitSet(_initError,0);
			return;
		}
		if (!SPI.pinIsChipSelect(_cs)) {//ERROR
			bitSet(_initError,1);
			return;
		}
	}
	#if defined(_TEENSYLC_FASTPORT)
		csportSet    	= portSetRegister(digitalPinToPort(_cs));
		csportClear     = portClearRegister(digitalPinToPort(_cs));
		cspinmask 		= digitalPinToBitMask(_cs);
		_dcState = 1;
		dcportSet       = portSetRegister(digitalPinToPort(_rs));
		dcportClear     = portClearRegister(digitalPinToPort(_rs));
		dcpinmask	    = digitalPinToBitMask(_rs);
	#endif
		#if !defined(_TEENSYLC_FASTPORT)
			digitalWriteFast(_cs,HIGH);
		#else
			*csportSet = cspinmask;
		#endif
		enableDataStream();
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	ST7735_SPI = SPISettings(30000000, MSBFIRST, SPI_MODE0);
	if ((_mosi == 11 || _mosi == 7) && (_sclk == 13 || _sclk == 14)) {
        SPI.setMOSI(_mosi);
        SPI.setSCK(_sclk);
	} else {
		bitSet(_initError,0);
		return;
	}
	SPI.begin();
	if (SPI.pinIsChipSelect(_cs, _rs)) {
		pcs_data = SPI.setCS(_cs);
		pcs_command = pcs_data | SPI.setCS(_rs);
	} else {
		pcs_data = 0;
		pcs_command = 0;
		bitSet(_initError,1);
		return;
	}
#else//all the rest of possible boards
	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	SPI.begin();
	#if !defined(SPI_HAS_TRANSACTION)
		SPI.setClockDivider(4);
		SPI.setBitOrder(MSBFIRST);
		SPI.setDataMode(SPI_MODE0);
	#else
		ST7735_SPI = SPISettings(8000000, MSBFIRST, SPI_MODE0);
	#endif
	digitalWrite(_cs,HIGH);
	enableDataStream();
#endif
	if (_rst != 255) {
		pinMode(_rst, OUTPUT);
		digitalWrite(_rst, HIGH);
		delay(500);
		digitalWrite(_rst, LOW);
		delay(500);
		digitalWrite(_rst, HIGH);
		delay(500);
	}

/*
7) MY:  1(bottom to top), 0(top to bottom) 	| Row Address Order
6) MX:  1(R to L),        0(L to R)        	| Column Address Order
5) MV:  1(Exchanged),     0(normal)        	| Row/Column exchange
4) ML:  1(bottom to top), 0(top to bottom) 	| Vertical Refresh Order
3) RGB: 1(BGR), 		  0(RGB)            | Color Space
2) MH:  1(R to L),        0(L to R)        	| Horizontal Refresh Order
1)
0)



	 7   6   5	(128x160 Gm=011)(132x162 Gm=000)
     MY, MX, MV
	 0 | 0 | 0 	// Col				| Row			Normal
	 1 | 0 | 0 	// Col	            | (H-1)-Row		Y-Mir
	 0 | 1 | 0 	// (W-1)-Col	    | Row			X-Mir
	 1 | 1 | 0 	// (W-1)-Col	    | (H-1)-Row		XY-Mir
	 0 | 0 | 1 	// Row  	        | Col			XY-Exc
	 1 | 0 | 1 	// (H-1)-Row  	    | Col			XY-Exc/Y-Mir	
	 0 | 1 | 1 	// Row  	        | (W-1)-Col		XY-Exc/X-Mir	
	 1 | 1 | 1 	// (H-1)-Row  	    | (W-1)-Col		XY-Exc/XY-Mir
	 
	 1 | 0 | 0 | 0 | 1 | 0 | x | x	//Y-Mirror
	 0 | 1 | 0 | 0 | 1 | 0 | x | x	//X-Mirror
	 1 | 1 | 0 | 0 | 1 | 0 | x | x	//X-Y-Mirror
	 0 | 0 | 1 | 0 | 1 | 0 | x | x	//X-Y Exchange
	 1 | 0 | 1 | 0 | 1 | 0 | x | x	//X-Y Exchange, Y-Mirror
	 0 | 1 | 1 | 0 | 1 | 0 | x | x	//XY exchange
	 1 | 1 | 1 | 0 | 1 | 0 | x | x
*/
	_Mactrl_Data = 0b00000000;
	_colorspaceData = __COLORSPC;//start with default data;
	chipInit();
}

uint8_t TFT_ST7735::getErrorCode(void) 
{
	return _initError;
}

void TFT_ST7735::chipInit() {
	// uint8_t i;
	startTransaction();
	sendCommand_cont(CMD_SWRESET);
	delay(130);//120
	sendCommand_cont(CMD_SLPOUT);
	delay(500);//150
		
	sendRegister_cont(_ST7735_FRMCTR1P,CMD_FRMCTR1);
	sendRegister_cont(_ST7735_FRMCTR2P,CMD_FRMCTR2);
	sendRegister_cont(_ST7735_FRMCTR3P,CMD_FRMCTR3);
	sendRegister_cont(_ST7735_INVCTR,CMD_DINVCTR);
	sendRegister_cont(_ST7735_PWCTR1,CMD_PWCTR1);
	sendRegister_cont(_ST7735_PWCTR2,CMD_PWCTR2);
	sendRegister_cont(_ST7735_PWCTR3,CMD_PWCTR3);
	sendRegister_cont(_ST7735_PWCTR4,CMD_PWCTR4);
	sendRegister_cont(_ST7735_PWCTR5,CMD_PWCTR5);
	sendRegister_cont(_ST7735_PWCTR6,CMD_PWCTR6);
	sendRegister_cont(_ST7735_VMCTR1,CMD_VCOMCTR1);
		
	sendCommand_cont(CMD_INVOFF);
		
	sendRegister_cont(_ST7735_MADCTL,CMD_MADCTL);
	sendRegister_cont(_ST7735_PIXFMT,CMD_PIXFMT);		
	sendRegister_cont(_ST7735_CASET,CMD_CASET);
	sendRegister_cont(_ST7735_RASET,CMD_RASET);
		
	#if defined(__GAMMASET1) || defined(__GAMMASET2) || defined(__GAMMASET3)
		sendRegister_cont(pGammaSet,CMD_PGAMMAC);
		sendRegister_cont(nGammaSet,CMD_NGAMMAC);
		delay(10);
	#endif
	sendCommand_cont(CMD_NORON);
	delay(10);
	sendCommand_cont(CMD_DISPON);//display ON 
	delay(1);
	//sendRegister_cont(_ST7735_DFUNCTR,CMD_DFUNCTR);


		// writecommand(CMD_VCOMOFFS);
		// writedata(0x40);//0x40
		// delay(1);
  
		// set scroll area (thanks Masuda)
		// writecommand(CMD_VSCLLDEF);
		// writedata16(__OFFSET);
		// writedata16(_GRAMHEIGH - __OFFSET);
		// writedata16(0);
		
		//colorSpace(_colorspaceData);
		
		//writecommand(CMD_RAMWR);//Memory Write
		 //delay(1);
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			writecommand_last(CMD_NOP);//bogus command to set HI the CS
		#endif
		endTransaction();
		setRotation(0);
	if (_bklPin != 255) digitalWrite(_bklPin,HIGH);
	fillScreen(_defaultBackground);
	
}

void TFT_ST7735::sendCommand_cont(const uint8_t cmd) 
{
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_cont(cmd);
	#else
		enableCommandStream(); spiwrite(cmd);
	#endif
}

bool TFT_ST7735::sendRegister_cont(const uint8_t reg[],const uint8_t cmd) 
{
	if (reg[0] > 0){
		uint8_t i;
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			writecommand_cont(cmd);
		#else
			enableCommandStream(); spiwrite(cmd);
			enableDataStream();
		#endif
		for (i=1;i<reg[0]+1;i++){
			#if defined(__MK20DX128__) || defined(__MK20DX256__)
				writedata8_cont(reg[i]);
			#else
				spiwrite(reg[i]);
			#endif
		}
		return true;
	}
	return false;
}

/*
Colorspace selection:
0: RGB
1: GBR
*/
void TFT_ST7735::colorSpace(uint8_t cspace) {
	if (cspace < 1){
		bitClear(_Mactrl_Data,3);   //RGB
	} else {
		bitSet(_Mactrl_Data,3);		//GBR
	}
}

void TFT_ST7735::invertDisplay(boolean i) {
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		startTransaction();
		writecommand_last(i ? CMD_INVON : CMD_INVOFF);
		endTransaction();
	#else
		writecommand(i ? CMD_INVON : CMD_INVOFF);
	#endif
}

void TFT_ST7735::display(boolean onOff) {
	if (onOff){
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_DISPON);
			endTransaction();
		#else
			writecommand(CMD_DISPON);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,HIGH);
	} else {
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_DISPOFF);
			endTransaction();
		#else
			writecommand(CMD_DISPOFF);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,LOW);
	}
}

/*
void TFT_ST7735::idleMode(boolean onOff) {
	if (onOff){
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_IDLEON);
			endTransaction();
		#else
			writecommand(CMD_IDLEON);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,LOW);
	} else {
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_IDLEOF);
			endTransaction();
		#else
			writecommand(CMD_IDLEOF);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,HIGH);
	}
}
*/

void TFT_ST7735::sleepMode(boolean mode) {
	if (mode){
		if (sleep == 1) return;//already sleeping
		sleep = 1;
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_SLPIN);
			endTransaction();
		#else
			writecommand(CMD_SLPIN);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,LOW);
		delay(5);//needed
	} else {
		if (sleep == 0) return; //Already awake
		sleep = 0;
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_last(CMD_SLPOUT);
			endTransaction();
		#else
			writecommand(CMD_SLPOUT);
		#endif
		if (_bklPin != 255) digitalWrite(_bklPin,HIGH);
		delay(120);//needed
	}
}


void TFT_ST7735::defineScrollArea(int16_t tfa, int16_t bfa){
	// if (_portrait){
		// swap(tfa,bfa);
	// }
	//int16_t vsa = _width - tfa - bfa;
    //int16_t vsa = _ST7735_TFTHEIGHT; - tfa - bfa;
    //if (vsa >= 0) {
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			startTransaction();
			writecommand_cont(CMD_VSCLLDEF);
			writedata16_cont(tfa);
			//writedata16_cont(vsa);
			writedata16_last(bfa);
			endTransaction();
		#else
			writecommand(CMD_VSCLLDEF);
			writedata16(tfa);
			//writedata16(vsa);
			writedata16(bfa);
		#endif
    //}
}

void TFT_ST7735::scroll(uint16_t adrs) {
	if (adrs <= _ST7735_TFTHEIGHT) {
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		startTransaction();
		writecommand_cont(CMD_VSSTADRS);
		writedata16_last(adrs);
		endTransaction();
	#else
		writecommand(CMD_VSSTADRS);
		writedata16(adrs);
	#endif
	}
}


//fast
void TFT_ST7735::fillScreen(uint16_t color) {
	uint16_t px;
	
	startTransaction();
	
	setAddrWindow_cont(0x00,0x00,_width,_height);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		for (px = 0;px < _GRAMSIZE; px++){
			writedata16_cont(color);
		}
		writecommand_last(CMD_NOP);
	#else
		enableDataStream();
		for (px = 0;px < _GRAMSIZE; px++){ spiwrite16(color); }
	#endif
	//set cursor to 0
	/*
	setAddrWindow_cont(0,0,0,0);
	_cursor_x = 0;
	_cursor_y = 0;
	endTransaction();
	*/
}


void TFT_ST7735::homeAddress() 
{
	setAddrWindow(0x00,0x00,_ST7735_TFTWIDTH,_ST7735_TFTHEIGHT);
}


void TFT_ST7735::setCursor(int16_t x, int16_t y,bool centerText) 
{
	if (boundaryCheck(x,y)) return;
	setAddrWindow(0x00,0x00,x,y);
	_cursor_x = x;
	_cursor_y = y;
	_centerText = centerText;
}

void TFT_ST7735::getCursor(int16_t &x, int16_t &y) 
{
	x = _cursor_x;
	y = _cursor_y;
}

//fast
void TFT_ST7735::drawPixel(int16_t x, int16_t y, uint16_t color) 
{
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;
	startTransaction();
	drawPixel_cont(x,y,color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}


void TFT_ST7735::setTextSize(uint8_t s) 
{
	_fontScaling = (s > 0) ? s : 1;
}

void TFT_ST7735::setTextColor(uint16_t color) 
{
	_textcolor = _textbgcolor = color;
}

void TFT_ST7735::setTextColor(uint16_t frgrnd, uint16_t bckgnd) 
{
	_textcolor = frgrnd;
	_textbgcolor = bckgnd;
}

void TFT_ST7735::setBackground(uint16_t color) 
{
	_defaultBackground = color;
}


void TFT_ST7735::setForeground(uint16_t color) 
{
	_defaultForeground = color;
}

uint16_t TFT_ST7735::getBackground(void) 
{
	return _defaultBackground;
}

uint16_t TFT_ST7735::getForeground(void) 
{
	return _defaultForeground;
}

void TFT_ST7735::setTextWrap(boolean w) 
{
	wrap = w;
}

uint8_t TFT_ST7735::getRotation(void)  
{
	return _rotation;
}

bool TFT_ST7735::boundaryCheck(int16_t x,int16_t y){
	if ((x >= _width) || (y >= _height)) return true;
	return false;
}



void TFT_ST7735::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	startTransaction();
	setAddrWindow_cont(x0,y0,x1,y1);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}


void TFT_ST7735::setRotation(uint8_t m) {
	_rotation = m % 4; // can't be higher than 3
	_Mactrl_Data &= ~(0xF0);//clear bit 4...7
	_width  = _ST7735_TFTWIDTH;
	_height = _ST7735_TFTHEIGHT;
	if (_rotation == 0){
		_portrait = false;
	} else if (_rotation == 1){
		bitSet(_Mactrl_Data,6);
		bitSet(_Mactrl_Data,5);
		_portrait = true;
	} else if (_rotation == 2){
		bitSet(_Mactrl_Data,7);
		bitSet(_Mactrl_Data,6);
		_portrait = false;
	} else {
		bitSet(_Mactrl_Data,7);
		bitSet(_Mactrl_Data,5);
		_portrait = true;
	}
	if (_portrait) swap(_width,_height);
	
	colorSpace(_colorspaceData);
	
	startTransaction();
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_cont(CMD_MADCTL);
		writedata8_last(_Mactrl_Data);
	#else
		enableCommandStream();
		spiwrite(CMD_MADCTL);
		enableDataStream();
		spiwrite(_Mactrl_Data);
	#endif
	endTransaction();
}

int16_t TFT_ST7735::width(void) const {
	return _width;
}
 
int16_t TFT_ST7735::height(void) const {
	return _height;
}

/* --------------------------------------------------------------------------------------------------
										GRAPHIC SUBS
-----------------------------------------------------------------------------------------------------*/


void TFT_ST7735::setFont(const tFont *font) 
{
	_currentFont = font;
	_fontHeight = 		_currentFont->font_height;
	_fontWidth = 		_currentFont->font_width;//if 0 it's variable
	_fontCompression = 	_currentFont->rle;
	//get one time all needed infos
	if (_fontWidth > 0){
		_spaceWidth = _fontWidth;
	} else {
		_spaceWidth = searchCharCode(0x20);
	}
	// Serial.println("---- setFont ----");
	// Serial.print("fontHeight:");
	// Serial.print(_fontHeight);
	// Serial.print(" | fontHeight:");
	// Serial.print(_fontWidth);
	// Serial.print(" | spaceWidth:");
	// Serial.print(_spaceWidth);
	// Serial.print("\n");
}

void TFT_ST7735::setFontInterline(uint8_t val) 
{
	_interline = val;
}


/*
draw fast vertical line
this uses fast contiguos commands method but opens SPi transaction and enable CS
then set CS hi and close transaction
*/
void TFT_ST7735::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
	// Rudimentary clipping
	if (boundaryCheck(x,y)) return;
	if (((y + h) - 1) >= _height) h = _height - y;
	startTransaction();
	drawFastVLine_cont(x,y,h,color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}


/*
draw fast horizontal line
this uses fast contiguos commands method but opens SPi transaction and enable CS
then set CS hi and close transaction
*/
void TFT_ST7735::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) 
{
	// Rudimentary clipping
	if (boundaryCheck(x,y)) return;
	if (((x + w) - 1) >= _width)  w = _width - x;
	startTransaction();
	drawFastHLine_cont(x,y,w,color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}


void TFT_ST7735::clearScreen(void) 
{
	fillScreen(_defaultBackground);
}

/*
fill RECT
*/
void TFT_ST7735::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
	if (boundaryCheck(x,y)) return;
	if (((x + w) - 1) >= _width)  w = _width  - x;
	if (((y + h) - 1) >= _height) h = _height - y;
	startTransaction();
	fillRect_cont(x,y,w,h,color);
	endTransaction();
}

void TFT_ST7735::fillRect_cont(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
	setAddrWindow_cont(x,y,(x+w)-1,(y+h)-1);
	#if !defined(__MK20DX128__) && !defined(__MK20DX256__)
		enableDataStream();
	#endif
	for (y = h;y > 0;y--) {
		for (x = w;x > 1;x--) {
			#if defined(__MK20DX128__) || defined(__MK20DX256__)
				writedata16_cont(color);
			#else
				spiwrite16(color);
			#endif
		}
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			writedata16_last(color);
		#else
			spiwrite16(color);
		#endif
	}
}

//80% fast
/*
draw LINE
*/
void TFT_ST7735::drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color)
{
	startTransaction();
	drawLine_cont(x0,y0,x1,y1,color);
	/*
	if (y0 == y1) {
		if (x1 > x0) {
			drawFastHLine(x0, y0, x1 - x0 + 1, color);
		} else if (x1 < x0) {
			drawFastHLine(x1, y0, x0 - x1 + 1, color);
		} else {
			drawPixel(x0, y0, color);
		}
		return;
	} else if (x0 == x1) {
		if (y1 > y0) {
			drawFastVLine(x0, y0, y1 - y0 + 1, color);
		} else {
			drawFastVLine(x0, y1, y0 - y1 + 1, color);
		}
		return;
	}

	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {swap(x0, y0); swap(x1, y1);}
	if (x0 > x1) {swap(x0, x1); swap(y0, y1);}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	startTransaction();
	
	int16_t xbegin = x0;
	if (steep) {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					drawFastVLine_cont(y0, xbegin, len + 1, color);
				} else {
					drawPixel_cont(y0, x0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) drawFastVLine_cont(y0, xbegin, x0 - xbegin, color);
	} else {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					drawFastHLine_cont(xbegin, y0, len + 1, color);
				} else {
					drawPixel_cont(x0, y0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) drawFastHLine_cont(xbegin, y0, x0 - xbegin, color);
	}
	*/
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}

void TFT_ST7735::drawLine_cont(int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color)
{
	if (y0 == y1) {
		if (x1 > x0) {
			drawFastHLine_cont(x0, y0, x1 - x0 + 1, color);
		} else if (x1 < x0) {
			drawFastHLine_cont(x1, y0, x0 - x1 + 1, color);
		} else {
			drawPixel_cont(x0, y0, color);
		}
		return;
	} else if (x0 == x1) {
		if (y1 > y0) {
			drawFastVLine_cont(x0, y0, y1 - y0 + 1, color);
		} else {
			drawFastVLine_cont(x0, y1, y0 - y1 + 1, color);
		}
		return;
	}

	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {swap(x0, y0); swap(x1, y1);}
	if (x0 > x1) {swap(x0, x1); swap(y0, y1);}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	int16_t xbegin = x0;
	if (steep) {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					drawFastVLine_cont(y0, xbegin, len + 1, color);
				} else {
					drawPixel_cont(y0, x0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) drawFastVLine_cont(y0, xbegin, x0 - xbegin, color);
	} else {
		for (; x0<=x1; x0++) {
			err -= dy;
			if (err < 0) {
				int16_t len = x0 - xbegin;
				if (len) {
					drawFastHLine_cont(xbegin, y0, len + 1, color);
				} else {
					drawPixel_cont(x0, y0, color);
				}
				xbegin = x0 + 1;
				y0 += ystep;
				err += dx;
			}
		}
		if (x0 > xbegin + 1) drawFastHLine_cont(xbegin, y0, x0 - xbegin, color);
	}
}

//fast
/*
draw rect
*/
void TFT_ST7735::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
	startTransaction();
		drawFastHLine_cont(x, y, w, color);
		drawFastHLine_cont(x, (y+h)-1, w, color);
		drawFastVLine_cont(x, y, h, color);
		drawFastVLine_cont((x+w)-1, y, h, color);	
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);//bogus command to set HI the CS
	#endif
	endTransaction();
}

//fast
void TFT_ST7735::drawArcHelper(uint16_t cx, uint16_t cy, uint16_t radius, uint16_t thickness, float start, float end, uint16_t color) 
{
	int16_t xmin = 65535, xmax = -32767, ymin = 32767, ymax = -32767;
	float cosStart, sinStart, cosEnd, sinEnd;
	float r, t;
	float startAngle, endAngle;

	startAngle = (start / _arcAngleMax) * 360;	// 252
	endAngle = (end / _arcAngleMax) * 360;		// 807

	while (startAngle < 0) startAngle += 360;
	while (endAngle < 0) endAngle += 360;
	while (startAngle > 360) startAngle -= 360;
	while (endAngle > 360) endAngle -= 360;


	if (startAngle > endAngle) {
		drawArcHelper(cx, cy, radius, thickness, ((startAngle) / 360.0) * _arcAngleMax, _arcAngleMax, color);
		drawArcHelper(cx, cy, radius, thickness, 0, ((endAngle) / 360.0) * _arcAngleMax, color);
	} else {
		// Calculate bounding box for the arc to be drawn
		cosStart = cosDegrees(startAngle);
		sinStart = sinDegrees(startAngle);
		cosEnd = cosDegrees(endAngle);
		sinEnd = sinDegrees(endAngle);

		r = radius;
		// Point 1: radius & startAngle
		t = r * cosStart;
		if (t < xmin) xmin = t;
		if (t > xmax) xmax = t;
		t = r * sinStart;
		if (t < ymin) ymin = t;
		if (t > ymax) ymax = t;

		// Point 2: radius & endAngle
		t = r * cosEnd;
		if (t < xmin) xmin = t;
		if (t > xmax) xmax = t;
		t = r * sinEnd;
		if (t < ymin) ymin = t;
		if (t > ymax) ymax = t;

		r = radius - thickness;
		// Point 3: radius-thickness & startAngle
		t = r * cosStart;
		if (t < xmin) xmin = t;
		if (t > xmax) xmax = t;
		t = r * sinStart;
		if (t < ymin) ymin = t;
		if (t > ymax) ymax = t;

		// Point 4: radius-thickness & endAngle
		t = r * cosEnd;
		if (t < xmin) xmin = t;
		if (t > xmax) xmax = t;
		t = r * sinEnd;
		if (t < ymin) ymin = t;
		if (t > ymax) ymax = t;
		// Corrections if arc crosses X or Y axis
		if ((startAngle < 90) && (endAngle > 90)) ymax = radius;
		if ((startAngle < 180) && (endAngle > 180)) xmin = -radius;
		if ((startAngle < 270) && (endAngle > 270)) ymin = -radius;

		// Slopes for the two sides of the arc
		float sslope = (float)cosStart / (float)sinStart;
		float eslope = (float)cosEnd / (float)sinEnd;
		if (endAngle == 360) eslope = -1000000;
		int ir2 = (radius - thickness) * (radius - thickness);
		int or2 = radius * radius;
		int x,y;
		startTransaction();
		for (x = xmin; x <= xmax; x++) {
			bool y1StartFound = false, y2StartFound = false;
			bool y1EndFound = false, y2EndSearching = false;
			int y1s = 0, y1e = 0, y2s = 0;//, y2e = 0;
			for (y = ymin; y <= ymax; y++) {
				int x2 = x * x;
				int y2 = y * y;

				if (
					(x2 + y2 < or2 && x2 + y2 >= ir2) && (
					(y > 0 && startAngle < 180 && x <= y * sslope) ||
					(y < 0 && startAngle > 180 && x >= y * sslope) ||
					(y < 0 && startAngle <= 180) ||
					(y == 0 && startAngle <= 180 && x < 0) ||
					(y == 0 && startAngle == 0 && x > 0)
					) && (
					(y > 0 && endAngle < 180 && x >= y * eslope) ||
					(y < 0 && endAngle > 180 && x <= y * eslope) ||
					(y > 0 && endAngle >= 180) ||
					(y == 0 && endAngle >= 180 && x < 0) ||
					(y == 0 && startAngle == 0 && x > 0)))
				{
					if (!y1StartFound) {	//start of the higher line found
						y1StartFound = true;
						y1s = y;
					} else if (y1EndFound && !y2StartFound) {//start of the lower line found
						y2StartFound = true;
						y2s = y;
						y += y1e - y1s - 1;	// calculate the most probable end of the lower line (in most cases the length of lower line is equal to length of upper line), in the next loop we will validate if the end of line is really there
						if (y > ymax - 1) {// the most probable end of line 2 is beyond ymax so line 2 must be shorter, thus continue with pixel by pixel search
							y = y2s;	// reset y and continue with pixel by pixel search
							y2EndSearching = true;
						}
					} else if (y2StartFound && !y2EndSearching) {
						// we validated that the probable end of the lower line has a pixel, continue with pixel by pixel search, in most cases next loop with confirm the end of lower line as it will not find a valid pixel
						y2EndSearching = true;
					}
				} else {
					if (y1StartFound && !y1EndFound) {//higher line end found
						y1EndFound = true;
						y1e = y - 1;
						drawFastVLine_cont(cx + x, cy + y1s, y - y1s, color);
						if (y < 0) {
							y = abs(y); // skip the empty middle
						}
						else
							break;
					} else if (y2StartFound) {
						if (y2EndSearching) {
							// we found the end of the lower line after pixel by pixel search
							drawFastVLine_cont(cx + x, cy + y2s, y - y2s, color);
							y2EndSearching = false;
							break;
						} else {
							// the expected end of the lower line is not there so the lower line must be shorter
							y = y2s;	// put the y back to the lower line start and go pixel by pixel to find the end
							y2EndSearching = true;
						}
					}
				}
			}
			if (y1StartFound && !y1EndFound){
				y1e = ymax;
				drawFastVLine_cont(cx + x, cy + y1s, y1e - y1s + 1, color);
			} else if (y2StartFound && y2EndSearching)	{// we found start of lower line but we are still searching for the end
														// which we haven't found in the loop so the last pixel in a column must be the end
				drawFastVLine_cont(cx + x, cy + y2s, ymax - y2s + 1, color);
			}
		}
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			writecommand_last(CMD_NOP);
		#endif
		endTransaction();
	}
}

float TFT_ST7735::cosDegrees(float angle)
{
	float radians = angle / (float)360 * 2 * PI;
	return cos(radians);
}

float TFT_ST7735::sinDegrees(float angle)
{
	float radians = angle / (float)360 * 2 * PI;
	return sin(radians);
}

void TFT_ST7735::setArcParams(float arcAngleMax, int arcAngleOffset)
{
	_arcAngleMax = arcAngleMax;
	_arcAngleOffset = arcAngleOffset;
}

/*
void TFT_ST7735::drawPie(int16_t x, int16_t y, int16_t r, int16_t rs, int16_t re,uint16_t color)
{
	int16_t px, py, cx, cy, d;
	rs -= 90;
	re   -= 90;
	if (rs>re) rs -= 360;
	px = x + cos((rs*3.14)/180) * r;
	py = y + sin((rs*3.14)/180) * r;
	drawLine(x, y, px, py,color);
	for (d=rs+1; d<re+1; d++){
		cx = x + cos((d*3.14)/180) * r;
		cy = y + sin((d*3.14)/180) * r;
		drawLine(px, py, cx, cy,color);
		px = cx;
		py = cy;
	}
	drawLine(x, y, px, py,color);
}
*/

//fast
void TFT_ST7735::drawEllipse(int16_t cx,int16_t cy,int16_t radiusW,int16_t radiusH,uint16_t color)
{
	int16_t x,y;
	int16_t twoASquare,twoBSquare;
	int32_t stoppingX,stoppingY;
    int32_t xchange,ychange,ellipseError;
    twoASquare = 2 * (radiusW * radiusW);
    twoBSquare = 2 * (radiusH * radiusH);
    x = radiusW;
    y = 0;
    xchange = (radiusH * radiusH) * (1 - (2 * radiusW));
    ychange = (radiusW * radiusW);
    ellipseError = 0;
    stoppingX = (twoBSquare * radiusW);
    stoppingY = 0;
	startTransaction();
    while (stoppingX >= stoppingY) {
		plot4points_cont(cx,cy,x,y,color);
		y++;
		stoppingY += twoASquare;
		ellipseError += ychange;
		ychange += twoASquare;
		if ((2 * ellipseError) + xchange > 0) {
			x--;
			stoppingX -= twoBSquare;
			ellipseError += xchange;
			xchange += twoBSquare;
		}
    }
    x = 0;
    y = radiusH;
    xchange = (radiusH * radiusH);
    ychange = (radiusW * radiusW) * (1 - (2 * radiusH));
    ellipseError = 0;
    stoppingX = 0;
    stoppingY = (twoASquare * radiusH);
    while (stoppingX <= stoppingY) {
		plot4points_cont(cx,cy,x,y,color);
		x++;
		stoppingX += twoBSquare;
		ellipseError += xchange;
		xchange += twoBSquare;
		if (((2 * ellipseError) + ychange) > 0) {
			y--;
			stoppingY -= twoASquare;
			ellipseError += ychange;
			ychange += twoASquare;
		}
    }
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();
}


/*
void TFT_ST7735::drawBezier(int x0, int y0, int x1, int y1, int x2, int y2,uint16_t color)
{
	int sx = x0 < x2 ? 1 : -1, sy = y0 < y2 ? 1 : -1; // step direction
	int cur = sx * sy * ((x0 - x1) * (y2 - y1) - (x2 - x1) * (y0 - y1)); // curvature
	int x = x0 - 2 * x1 + x2, y = y0 - 2 * y1 + y2, xy = 2 * x * y * sx * sy;
                                // compute error increments of P0
	long dx = (1 - 2 * abs(x0 - x1)) * y * y + abs(y0 - y1) * xy - 2 * cur * abs(y0 - y2);
	long dy = (1 - 2 * abs(y0 - y1)) * x * x + abs(x0 - x1) * xy + 2 * cur * abs(x0 - x2);
                                // compute error increments of P2 
	long ex = (1 - 2 * abs(x2 - x1)) * y * y + abs(y2 - y1) * xy + 2 * cur * abs(y0 - y2);
	long ey = (1 - 2 * abs(y2 - y1)) * x * x + abs(x2 - x1) * xy - 2 * cur * abs(x0 - x2);

	if (cur == 0) { drawLine(x0, y0, x2, y2, color); return; } // straight line 

	x *= 2 * x; y *= 2 * y;
	if (cur < 0) { // negated curvature 
		x = -x; dx = -dx; ex = -ex; xy = -xy;
		y = -y; dy = -dy; ey = -ey;
	}
  // algorithm fails for almost straight line, check error values 
	if (dx >= -y || dy <= -x || ex <= -y || ey >= -x) {
		drawLine(x0, y0, x1, y1, color); // simple approximation 
		drawLine(x1, y1, x2, y2, color);
		return;
	}
	dx -= xy; ex = dx+dy; dy -= xy; // error of 1.step 

	for(;;) { // plot curve
		drawPixel(y0, x0, color);
		ey = 2 * ex - dy; // save value for test of y step 
		if (2 * ex >= dx) { // x step
			if (x0 == x2) break;
			x0 += sx; dy -= xy; ex += dx += y;
		}
		if (ey <= 0) { // y step 
			if (y0 == y2) break;
			y0 += sy; dx -= xy; ex += dy += x;
		}
	}
}
*/


//fast
void TFT_ST7735::drawCircle(int16_t cx, int16_t cy, int16_t radius, uint16_t color)
{
	int error = -radius;
	int16_t x = radius;
	int16_t y = 0;
	startTransaction();
	while (x >= y){
		plot4points_cont(cx, cy, x, y, color);
		if (x != y) plot4points_cont(cx, cy, y, x, color);
		error += y;
		++y;
		error += y;
		if (error >= 0){
			--x;
			error -= x;
			error -= x;
		}
	}
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();
}


//fast
void TFT_ST7735::drawRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color) 
{
	startTransaction();
	drawFastHLine_cont(x+r  , y    , w-2*r, color); // Top
	drawFastHLine_cont(x+r  , y+h-1, w-2*r, color); // Bottom
	drawFastVLine_cont(x    , y+r  , h-2*r, color); // Left
	drawFastVLine_cont(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
	drawCircle_cont(x+r    , y+r    , r, 1, color);
	drawCircle_cont(x+w-r-1, y+r    , r, 2, color);
	drawCircle_cont(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircle_cont(x+r    , y+h-r-1, r, 8, color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();
}


//fast
void TFT_ST7735::fillRoundRect(int16_t x, int16_t y, int16_t w,int16_t h, int16_t r, uint16_t color) 
{
	startTransaction();
	fillRect_cont(x+r, y, w-2*r, h, color);
	fillCircle_cont(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircle_cont(x+r    , y+r, r, 2, h-2*r-1, color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();
}

//fast
void TFT_ST7735::fillCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color) 
{
	startTransaction();//open SPI comm
	drawFastVLine_cont(x0, y0-r, 2*r+1, color);
	fillCircle_cont(x0, y0, r, 3, 0, color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}


void TFT_ST7735::drawQuad(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2,int16_t x3, int16_t y3, uint16_t color) 
{
	startTransaction();//open SPI comm
	drawLine_cont(x0, y0, x1, y1, color);//low 1
	drawLine_cont(x1, y1, x2, y2, color);//high 1
	drawLine_cont(x2, y2, x3, y3, color);//high 2
	drawLine_cont(x3, y3, x0, y0, color);//low 2
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}


void TFT_ST7735::fillQuad(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t color) 
{
	startTransaction();//open SPI comm
    fillTriangle_cont(x0,y0,x1,y1,x2,y2,color);
    fillTriangle_cont(x0,y0,x2,y2,x3,y3,color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}

void TFT_ST7735::drawPolygon(int16_t cx, int16_t cy, uint8_t sides, int16_t diameter, float rot, uint16_t color)
{ 
	sides = (sides > 2? sides : 3);
	float dtr = (PI/180.0) + PI;
	float rads = 360.0 / sides;//points spacd equally
	uint8_t i;
	startTransaction();
	for (i = 0; i < sides; i++) { 
		drawLine_cont(
			cx + (sin((i*rads + rot) * dtr) * diameter),
			cy + (cos((i*rads + rot) * dtr) * diameter),
			cx + (sin(((i+1)*rads + rot) * dtr) * diameter),
			cy + (cos(((i+1)*rads + rot) * dtr) * diameter),
			color);
	}
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}

void TFT_ST7735::drawMesh(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	if (boundaryCheck(x,y)) return;
	if (((x + w) - 1) >= _width)  w = _width  - x;
	if (((y + h) - 1) >= _height) h = _height - y;
	
	int16_t n, m;

	if (w < x) {n = w; w = x; x = n;}
	if (h < y) {n = h; h = y; y = n;}
	startTransaction();
	for (m = y; m <= h; m += 2) {
		for (n = x; n <= w; n += 2) {
			drawPixel_cont(n, m, color);
		}
	}
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}

void TFT_ST7735::drawTriangle(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color) 
{
	startTransaction();
	drawLine_cont(x0, y0, x1, y1, color);
	drawLine_cont(x1, y1, x2, y2, color);
	drawLine_cont(x2, y2, x0, y0, color);
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}

//85% fast
void TFT_ST7735::fillTriangle(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color) 
{
	
	startTransaction();
	fillTriangle_cont(x0,y0,x1,y1,x2,y2,color);//
	#if defined(__MK20DX128__) || defined(__MK20DX256__)	
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();//close SPI comm
}

void TFT_ST7735::fillTriangle_cont(int16_t x0, int16_t y0,int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color) 
{
	int16_t a, b, y, last;

	if (y0 > y1) {swap(y0, y1); swap(x0, x1);}
	if (y1 > y2) {swap(y2, y1); swap(x2, x1);}
	if (y0 > y1) {swap(y0, y1); swap(x0, x1);}

	if (y0 == y2) {
		a = b = x0;
		if (x1 < a){
			a = x1;
		} else if (x1 > b) {
			b = x1;
		}
		if (x2 < a){
			a = x2;
		} else if (x2 > b) {
			b = x2;
		}
		drawFastHLine_cont(a, y0, b-a+1, color);
		return;
	}

	int16_t
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1;
	int32_t
		sa   = 0,
		sb   = 0;

	if (y1 == y2) {
		last = y1;
	} else { 
		last = y1-1;
	}

	for (y=y0; y<=last; y++) {
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		if (a > b) swap(a,b);
		drawFastHLine_cont(a, y, b-a+1, color);
	}

	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if (a > b) swap(a,b);
		drawFastHLine_cont(a, y, b-a+1, color);
	}
}

//fast
void TFT_ST7735::plot4points_cont(uint16_t cx, uint16_t cy, uint16_t x, uint16_t y, uint16_t color)
{
	drawPixel_cont(cx + x, cy + y, color);
	if (x != 0) drawPixel_cont(cx - x, cy + y, color);
	if (y != 0) drawPixel_cont(cx + x, cy - y, color);
	if (x != 0 && y != 0) drawPixel_cont(cx - x, cy - y, color);
}

//fast
void TFT_ST7735::drawCircle_cont(int16_t x0,int16_t y0,int16_t r,uint8_t cornername,uint16_t color) 
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;
	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4) {
			drawPixel_cont(x0 + x, y0 + y, color);
			drawPixel_cont(x0 + y, y0 + x, color);
		} 
		if (cornername & 0x2) {
			drawPixel_cont(x0 + x, y0 - y, color);
			drawPixel_cont(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			drawPixel_cont(x0 - y, y0 + x, color);
			drawPixel_cont(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			drawPixel_cont(x0 - y, y0 - x, color);
			drawPixel_cont(x0 - x, y0 - y, color);
		}
	}
}

//fast
void TFT_ST7735::fillCircle_cont(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) 
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			drawFastVLine_cont(x0+x, y0-y, 2*y+1+delta, color);
			drawFastVLine_cont(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			drawFastVLine_cont(x0-x, y0-y, 2*y+1+delta, color);
			drawFastVLine_cont(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}



//fast
void TFT_ST7735::startPushData(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	startTransaction();
	setAddrWindow_cont(x0,y0,x1,y1);
	#if !defined(__MK20DX128__) && !defined(__MK20DX256__)
		enableDataStream();
	#endif
}


//fast
void TFT_ST7735::pushData(uint16_t color) {
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writedata16_cont(color);
	#else
		spiwrite16(color);
	#endif
}

//fast
void TFT_ST7735::endPushData() {
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);
	#endif
	endTransaction();
}

//fast
void TFT_ST7735::pushColor(uint16_t color) {
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		startTransaction();
		writedata16_last(color);
		endTransaction();
	#else
		writedata16(color);
	#endif
}



//fast
void TFT_ST7735::drawColorBitmap(int16_t x, int16_t y, int16_t w, int16_t h, const uint32_t *bitmap,bool true24) 
{
	int16_t px;
	uint16_t color;
	
	startTransaction();
	setAddrWindow_cont(x,y,w,h);//constrain window
	#if !defined(__MK20DX128__) && !defined(__MK20DX256__)
		enableCommandStream();
		spiwrite(CMD_RAMWR);
		enableDataStream();
	#else
		writecommand_cont(CMD_RAMWR);//ram write
	#endif
	for (px = 0;px < w*h; px++){//loop trough pixels
		if (true24){
			color = Color24To565(bitmap[px]);//24 bit
		} else {
			color = bitmap[px];//18 bit
		}
		#if defined(__MK20DX128__) || defined(__MK20DX256__)
			writedata16_cont(color);
		#else
			spiwrite16(color);
		#endif
	}
	#if defined(__MK20DX128__) || defined(__MK20DX256__)
		writecommand_last(CMD_NOP);//just for set CS hi
	#endif
	endTransaction();
}


void TFT_ST7735::drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color) 
{
	int16_t i, j, byteWidth = (w + 7) / 8;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++ ) {
			if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) drawPixel(x+i, y+j, color);
		}
	}
}

void TFT_ST7735::drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color, uint16_t bg) 
{
	int16_t i, j, byteWidth = (w + 7) / 8;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++ ) {
			if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
				drawPixel(x+i, y+j, color);
			} else {
				drawPixel(x+i, y+j, bg);
		}
    }
  }
}

int TFT_ST7735::searchCharCode(uint8_t ch)
{
	int i;
	for (i=0;i<_currentFont->length;i++){//search for char code
		#if defined(_FORCE_PROGMEM__)
			
			//uint8_t ccode = pgm_read_byte(&_currentFont->chars[i].char_code);
			//uint8_t ccode = PROGMEM_GET(&_currentFont->chars[i].char_code);
			//uint8_t ccode = pgm_read_byte(_currentFont->chars[i].char_code);
			uint8_t ccode = _currentFont->chars[i].char_code;
			if (ccode == ch){//found char!
				 // Serial.println("\n--- searchCharCode ---");
				 // Serial.print("len:");
				 // Serial.print(_currentFont->length,DEC);
				 // Serial.print(" | charCode:0x");
				 // Serial.print(ccode);
				 // Serial.print(" | index:");
				 // Serial.print(i);
				return i;
			}
		#else
			if (_currentFont->chars[i].char_code == ch){//found char!
				return i;
			}
		#endif
	}//i
	return -1;
}

void TFT_ST7735::textWrite(const char* buffer, uint16_t len)
{
	uint16_t i;
	int charIndex = -1;
	uint8_t currCharWidth = 0;
	if (len == 0) len = strlen(buffer);
	//todo, fix issue if theres several spaces inside text
	if (_centerText){
		_centerText = false;
		if (_fontWidth > 0){//fixed w
			_cursor_x = _cursor_x - (((len * _spaceWidth) * _fontScaling)/2);
		} else {//variable width
			uint16_t totW = 0;
			
			for (i=0;i<len;i++){//loop trough buffer
				if (buffer[i] != 13 && buffer[i] != 10){//avoid special char
					charIndex = searchCharCode(buffer[i]);
					if (charIndex > -1) {
						#if defined(_FORCE_PROGMEM__)
							currCharWidth = PROGMEM_read(&_currentFont->chars[charIndex].image->image_width);
							totW += (currCharWidth * _fontScaling);
						#else
							totW += (_currentFont->chars[charIndex].image->image_width * _fontScaling);
						#endif

					}
				}
			}
			_cursor_x = _cursor_x - (totW / 2);
		}
		_cursor_y = _cursor_y - (_fontHeight * _fontScaling)/2  - _fontScaling;
		setCursor(_cursor_x,_cursor_y,false);
	}

	for (i=0;i<len;i++){
		if (buffer[i] == 13){										//\r
			//nothing
		} else if (buffer[i] == 10){								//\n
			_cursor_y += (_fontHeight*_fontScaling) + _interline;
			_cursor_x  = 0;
		} else {													//chars
			charIndex = searchCharCode(buffer[i]);
			if (charIndex > -1){//valid?
				//Serial.println("\nchar exists");
				startTransaction();
				if (buffer[i] == 0x20){								//space
					uint16_t bcol;
					if (_textcolor != _textbgcolor){
						bcol = _textbgcolor;
					} else {
						bcol = _defaultBackground;
					}
					fillRect_cont(
								_cursor_x,
								_cursor_y,
								(_spaceWidth * _fontScaling),
								(_fontHeight * _fontScaling),
								bcol
					);
					_cursor_x = _cursor_x + (_spaceWidth * _fontScaling);
				} else {											// all chars
					#if defined(_FORCE_PROGMEM__)
						currCharWidth = PROGMEM_read(&_currentFont->chars[charIndex].image->image_width);
						const uint8_t * charGlyps = PROGMEM_read(&_currentFont->chars[charIndex].image->data);
					#else
						currCharWidth = _currentFont->chars[charIndex].image->image_width;
						const uint8_t * charGlyps = _currentFont->chars[charIndex].image->data;
					#endif
					
					//#if defined(_FORCE_PROGMEM__)
						// Serial.print("\ncharW:");
						// Serial.print(currCharWidth,DEC);
						// Serial.print("\n");
						//Serial.println(PROGMEM_read(&charGlyps[0]),HEX);
						
						if (_fontCompression){
							drawChar_compressed(
										_cursor_x,
										_cursor_y,
										currCharWidth,
										_fontHeight,
										charGlyps
							);
						} else {
							drawChar_uncompressed(
										_cursor_x,
										_cursor_y,
										currCharWidth,
										charGlyps
							);
						}
						
						
						if (_textcolor != _textbgcolor) {
							fillRect_cont(
									_cursor_x + (currCharWidth * _fontScaling),
									_cursor_y,
									_fontScaling,
									(_fontHeight * _fontScaling),
									_textbgcolor
							);
						}
						
						_cursor_x += currCharWidth * _fontScaling;
						if (wrap && (_cursor_x > (_width - (currCharWidth *_fontScaling)))) {
							_cursor_y += (_fontHeight * _fontScaling) + _interline;
							_cursor_x = 0;
						}
				}
				#if defined(__MK20DX128__) || defined(__MK20DX256__)	
					writecommand_last(CMD_NOP);
				#endif
				endTransaction();
			}//valid
		}//chars
	}//for loop
}

//TODO Use line writing (by using buffer) instead drawPixel_cont
void TFT_ST7735::drawChar_uncompressed(int16_t x,int16_t y,int16_t w,const uint8_t *data)
{
	if ((x >= _width)             			||  // Clip right
		(y >= _height)           			||  // Clip bottom
		((x + w * _fontScaling - 1) < 0) 	||  // Clip left
		((y + _fontHeight * _fontScaling - 1) < 0))   	// Clip top
    return;

	uint16_t bitCount = 0;
	uint16_t line = 0;
	int j;
	uint16_t i;//,idx;
	//uint16_t buffer[w*_fontScaling];//temp buffer
	for (i=0; i<_fontHeight; i++ ) {	//Y
		//idx = 0;
		for (j = 0; j<w; j++) {			//X		
			if (bitCount++%8 == 0) {
				#if defined(_FORCE_PROGMEM__)
					line = PROGMEM_read(&*data++);
				#else
					line = *data++;
				#endif
			}
			if (line & 0x80) {
				if (_fontScaling > 1) {//big
					fillRect_cont(x+(j*_fontScaling), y+(i*_fontScaling), _fontScaling, _fontScaling, _textcolor);
				} else {  // default size
					drawPixel_cont(x+j, y+i, _textcolor);
				} 
			} else if (_textbgcolor != _textcolor) {
				if (_fontScaling > 1) {// big
					fillRect_cont(x+(j*_fontScaling), y+(i*_fontScaling), _fontScaling, _fontScaling, _textbgcolor);
				} else {  // def size
					drawPixel_cont(x+j, y+i, _textbgcolor);
				}
			}		
			line <<= 1;
			//idx++;
		}
	}
}

//NOT Finished
void TFT_ST7735::drawChar_compressed(int16_t x, int16_t y,int16_t w,int16_t h,const uint8_t *pdata)
{

    int next = 0;

    int16_t cwidth;
	uint16_t size = w * h;
    int16_t i, k;
    int cnt, c, v;

	setAddrWindow_cont(x,y,(x + w)-1,(y - h)-1);
	#if !defined(__MK20DX128__) && !defined(__MK20DX256__)
		enableDataStream();
	#endif
	y = 0;
	cwidth = 0;
	while (size > 0) {
		#if defined(_FORCE_PROGMEM__)
		if (!next){
			c = (PROGMEM_read(&*pdata) >> 8) & 0xff;
		} else {
			c = PROGMEM_read(&*pdata) & 0xff;
			pdata++;
		}
		#else
		if (!next){
			c = (*pdata >> 8) & 0xff;
		} else {
			c = *pdata & 0xff;
			*pdata++;
		}
		#endif
		next ^= 1;
		if (c > 128) {
			cnt = c - 128;
			for (i = 0; i < cnt; i++){
				#if defined(_FORCE_PROGMEM__)
				if (!next){
					c = (PROGMEM_read(&*pdata) >> 8) & 0xff;
				} else {
					c = PROGMEM_read(&*pdata) & 0xff;
					pdata++;
				}
				#else
				if (!next){
					c = (*pdata >> 8) & 0xff;
				} else {
					c = *pdata & 0xff;
					*pdata++;
				}
				#endif
				next ^= 1;
				if (cwidth < 1) {
					cwidth = w;
					y++;
				}
				for (k = 0; k < 8 && cwidth > 0; k++, c <<= 1, size--, cwidth--){
					if ((c & 0x80) != 0) {
						#if defined(__MK20DX128__) || defined(__MK20DX256__)
							writedata16_cont(_textcolor);
						#else
							spiwrite16(_textcolor);
						#endif
						//Serial.print("*");
					} else {
						#if defined(__MK20DX128__) || defined(__MK20DX256__)
							writedata16_cont(_textbgcolor);
						#else
							spiwrite16(_textbgcolor);
						#endif
						//Serial.print(" ");
					}
				}
				//Serial.print("\n");
			}
		} else {
			cnt = c;
			#if defined(_FORCE_PROGMEM__)
			if (!next){
				c = (PROGMEM_read(&*pdata) >> 8) & 0xff;
			} else {
				c = PROGMEM_read(&*pdata) & 0xff;
				pdata++;
			}
			#else
			if (!next){
				c = (*pdata >> 8) & 0xff;
			} else {
				c = *pdata & 0xff;
				*pdata++;
			}
			#endif
			next ^= 1;
			for (i = 0; i < cnt; i++){
				v = c;
				if (cwidth < 1) {
					cwidth = w;
					y++;
				}
				for (k = 0; k < 8 && cwidth > 0; k++, v <<= 1, size--, cwidth--){
					if ((v & 0x80) != 0) {
						#if defined(__MK20DX128__) || defined(__MK20DX256__)
							writedata16_cont(_textcolor);
						#else
							spiwrite16(_textcolor);
						#endif
						//Serial.print("*");
					} else {
						#if defined(__MK20DX128__) || defined(__MK20DX256__)
							writedata16_cont(_textbgcolor);
						#else
							spiwrite16(_textbgcolor);
						#endif
						//Serial.print(" ");
					}
				}
				//Serial.print("\n");
			}
		}
	}

}

