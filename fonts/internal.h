#ifndef _ST7735_INTERNAL_FONT_H
#define _ST7735_INTERNAL_FONT_H
#include <stdio.h>
	#if defined(_FORCE_PROGMEM__)
		#include "internal_prgm.c"
	#else
		#include "internal.c"
	#endif
#endif