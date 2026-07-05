//
// Video.h: Video code, header file
//
#ifndef __VIDEO_H
#define __VIDEO_H

#define makewhite(a)		(makecol(a, a, a))

#define GETR		getr32
#define GETG		getg32
#define GETB		getb32
#define MAKECOL	makecol32
#define PUTPIXEL	_putpixel32
#define GETPIXEL _getpixel32

enum E_Colors {
	C_Black,
	C_GrayD,
	C_Gray,
	C_GrayH,
	C_White,
	C_RedD,
	C_Red,
	C_RedH,
	C_YellowD,
	C_Yellow,
	C_YellowH,
	C_GreenD,
	C_Green,
	C_GreenH,
	C_CyanD,
	C_Cyan,
	C_CyanH,
	C_BlueD,
	C_Blue,
	C_BlueH,
	C_Pink,
	C_MAX
};


extern BITMAP *VBuffer;
/*
==========
VideoInit
==========
	Initializes video system. Returns 0 on error.
*/
int VideoInit(void);

/*
============
VideoDeInit
============
	Deinitializes video system. 
*/
void VideoDeinit(void);

/*
================
VideoSwitchPage
================
	Switches current draw surface when using triple buffering.
*/
void VideoSwitchPage(void);

/*
===============
VideoDrawFrame
===============
	Draws the video buffer to screen when not using triple buffering.
*/
void VideoDrawFrame(void);

/*
=========
FontInit
=========
	Load font resources.
*/
int FontInit(void);

/*
===============
VideoDrawFrame
===============
	Unload font resources.
*/
void FontDeinit(void);


void Average(BITMAP *bmp);
void Blend(BITMAP *bmp);
void AddSky(BITMAP *bmp);

#endif
