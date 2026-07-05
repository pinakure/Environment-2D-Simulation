//
//	Common.h: Gemz main header
//

#ifndef __COMMON_H
#define __COMMON_H

//
// System includes
//
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable: 4996)
#pragma warning(disable: 4312)
#pragma warning(disable: 4075)
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>

#define true 1
#define false 0

#define FPS		60
#define TimeDT	(1.0f / (float) FPS)

#define VWIDTH	320
#define VHEIGHT	240

#include "Profile.h"

extern int  COLOR_PINK, 
			COLOR_WHITE, 
			COLOR_RED, 
			COLOR_YELLOW,
			COLOR_GREEN,
			COLOR_BLUE,
			COLOR_PURPLE,
			COLOR_VIOLET,
			COLOR_BROWN,
			COLOR_ORANGE;

extern int MouseX, MouseY;


enum E_EngineModes {
	EM_Game,
	EM_Editor,
	EM_Menu,
	EM_PreTitle,

	// PUT NODRAW MODES DOWN HERE
	EM_NoDraw,
	EM_Exit,
	EM_Init,	
	EM_Deinit
};

int SumColors(int a, int b);


void Deinit(void);
int Init(void);

int GetRand3(void);
int GetRand(void);

extern volatile unsigned int EngineFrames,
							 EngineFPS,
							 EngineDrawFPS,
							 EnginePeakFPS,EngineDrive,EngineTicks;


//
// Game includes
//
//#include "Sound.h"			//Sound code
#include "Fixed.h"
#include "Video.h"			//Video code
#include "Enviroment.h"
#endif
