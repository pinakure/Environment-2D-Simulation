#include "Common.h"

int COLOR_WHITE, 
	COLOR_PINK, 
	COLOR_RED, 
	COLOR_YELLOW, 
	COLOR_BLUE, 
	COLOR_GREEN,
	COLOR_PURPLE,
	COLOR_VIOLET,
	COLOR_BROWN,
	COLOR_ORANGE;


static PALETTE VideoPalette;

/* Exported variables */
BITMAP		*VBuffer;

int VideoInit(void)
{
	int v=0;

	set_color_depth(32);

#ifdef FULLSCREEN

#ifdef LINUX
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, VWIDTH*2, VHEIGHT*2, 0, 0);
#else
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, VWIDTH, VHEIGHT, 0, 0);
#endif

#else
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, VWIDTH, VHEIGHT, 0, 0);
#endif

	VBuffer = create_bitmap(VWIDTH, VHEIGHT);
	if(!VBuffer) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Can't setup video mode:73");
		return 0;
	}
	clear_bitmap(VBuffer);

	COLOR_WHITE = MAKECOL(168, 158, 205);
	COLOR_PINK  = MAKECOL(255, 0, 255);
	COLOR_RED	= MAKECOL(255, 0, 0);
	COLOR_YELLOW= MAKECOL(255, 255, 0);
	COLOR_BLUE	= MAKECOL(0, 255, 255);
	COLOR_GREEN = MAKECOL(0, 255, 0);
	COLOR_ORANGE= MAKECOL(255, 128, 0);
	COLOR_PURPLE= MAKECOL(128, 64, 128);
	COLOR_VIOLET= MAKECOL(64, 32, 64);
	COLOR_BROWN = MAKECOL(128, 64, 0);
	return 1;
}

void VideoDeinit(void)
{	
	destroy_bitmap(VBuffer);
}

/* TRIPLE BUFFERING FUNCTIONS */
void VideoSwitchPage(void)
{	
	clear_bitmap(VBuffer);
}

void VideoDrawFrame(void)
{
	static int clockx=0, clockv;
	static int rtime=0;
	static int rstate=0;
	static int EngineOFPS=0;

	masked_blit(EFXFade, VBuffer, 0, 0, 0, 0, VWIDTH, VHEIGHT);

	
	if(!rtime)
	{
		Average(EFXFade);		
	}
		
	rtime++;
	rtime&=3;
/*
	if(EngineDrawFPS)
	{
		clockv = (clockx%10)*16;
		line(EFXBuffer, 70, 200+(clockx&31), 70+(EngineOFPS>>2), 200+(clockx&31), COLOR_RED);
		//line(EFXBuffer, 70+(EngineOFPS>>2), 200+(clockx&31), VWIDTH, 200+(clockx&31), COLOR_VIOLET+clockv);
		EngineOFPS = EngineFPS;
		line(EFXBuffer, 70, 200+(clockx&31), 70+(EngineFPS>>2), 200+(clockx&31), COLOR_YELLOW);
		line(EFXBuffer, 70+(EngineFPS>>2), 201+(clockx&31), VWIDTH, 201+(clockx&31), COLOR_PINK);
		
		textprintf_ex(EFXBuffer, font, 0, 200, COLOR_YELLOW, COLOR_PINK, " [ FPS:%03u ] ", EngineFPS);
		EngineDrawFPS=0;
		clockx++;
	}
*/
	masked_blit(EFXClear, VBuffer, 0, 0, 0, 0, VWIDTH, VHEIGHT);
	masked_blit(EFXBuffer, VBuffer, 0, 0, 0, 0, VWIDTH, VHEIGHT);
	clear_to_color(EFXClear, COLOR_PINK);

	
	if(EnvControl.quake&&!key[KEY_SPACE])
	{
//		blit(VBuffer, screen,0, 0, (GetRand()&3)-1, (GetRand()&3)-1, VWIDTH, VHEIGHT);
		stretch_blit(VBuffer, screen,0, 0, VWIDTH, VHEIGHT, (GetRand()&3)-1, (GetRand()&3)-1, VWIDTH*2, VHEIGHT*2);
	}
	else 
	{
		if(key[KEY_SPACE])DrawProfiler();//masked_blit(ProfileBuffer, VBuffer, 0, 0, 0, 0, VWIDTH, VHEIGHT);
		blit(VBuffer, screen,0, 0, 0, 0, VWIDTH, VHEIGHT);
		//stretch_blit(VBuffer, screen,0, 0, VWIDTH, VHEIGHT, 0, 0, VWIDTH*2, VHEIGHT*2);

	}
	
	EngineFrames++;	
}

//SFX

void Blend(BITMAP *bmp)
{
	#define BLEND_FADE	4
	/*
	int x; 
	int y;
	int c;
	
	int sr, sg, sb;
	int r, g, b;
	int p[2];

	static int xphase = 0;
	static int yphase = 0;
	
	//StartProfiler(PROFILE_BLENDTICK);
	line(bmp, 0, bmp->h-1, bmp->w-1, bmp->h-1, 0);

	yphase^=1;

	for(y=yphase;y<VHEIGHT-1; y+=2)
	{
		xphase ^=1;		
		for(x=xphase; x<VWIDTH; x+=2)
		{
			p[0] = GETPIXEL(bmp, x, y);
			if(p[0]==COLOR_PINK)p[0]=0;

			p[1] = GETPIXEL(EFXSky, x, y);
			
			r = ( GETR(p[0]));//-BLEND_FADE;
			g = ( GETG(p[0]));//-BLEND_FADE;
			b = ( GETB(p[0]));//-BLEND_FADE;
			sr = GETR(p[1]);
			sg = GETG(p[1]);
			sb = GETB(p[1]);
			if(r>sr)
			{
				r-=BLEND_FADE;
				if(r<sr)r=sr;
			} else {
				r+=BLEND_FADE;
				if(r>sr)r=sr;
			}
			if(g>sg)
			{
				g-=BLEND_FADE;
				if(g<sg)g=sg;
			} else {
				g+=BLEND_FADE;
				if(g>sg)g=sg;
			}
			if(b>sb)
			{
				b-=BLEND_FADE;
				if(b<sb)b=sb;
			} else {
				b+=BLEND_FADE;
				if(b>sb)b=sb;
			}

			c = MAKECOL(r, g, b);

			PUTPIXEL(bmp, x,y, c);
		}
	}	*/
	
	//StopProfiler(PROFILE_BLENDTICK);
	//REPORT(190, BLEND_SCALE, BLENDTICK__, COLOR_BROWN);
}

//#define GETPIXEL(b,x,y) ((unsigned long *) b->line[y])[x]

int SumColors(int a, int b)
{
	return(MAKECOL((GETR(a)+GETR(b))>>1,
					(GETG(a)+GETG(b))>>1,
					(GETB(a)+GETB(b))>>1));					
}

int SumColors2(int A, int B)
{
	// TODO:
	return SumColors(A, B);
}

//#define MMX

void Average(BITMAP *bmp)
{
	#define AVERAGE_FADE 1//16
	int x; 
	int y;
	int c;

//	int r, g, b;
	int p[4];
	int sp;
	int dx;
//	int spr;
//	int spg;
//	int spb;
		
	static int xphase = 0;
	static int yphase = 0;

	unsigned long *p1, *p2, *p3;

	StartProfiler(PROFILE_AVERAGETICK);

	line(bmp, 0, bmp->h-1, bmp->w-1, bmp->h-1, 0);
	
	yphase^=1;

	dx = xphase;

	for(y=yphase;y<VHEIGHT-1; y+=2)
	{
		//xphase ^= 1;
		dx ^= 1;

		p1 = (unsigned long *) bmp->line[y];
		p2 = p1 + VWIDTH;
		p3 = (unsigned long *) EFXSky->line[y];

		for(x=dx; x<VWIDTH; x+=2)
		{
			sp = *p3++;

			p[2] = *p1++;
			p[0] = *p1++;
			p[3] = *p2++;
			p[1] = *p2++;

			p[0] += 0x00010001;
			p[1] += 0x00010001;
			p[2] += 0x00010001;
			p[3] += 0x00010001;

			//
			// NOTE: there's a bottleneck here:
			// less calls to SumColors2 = more speed
			//

#ifdef MMX
			__asm {
				movd mm0, sp
				movd mm1, p[0]
				movd mm2, p[1]
				movd mm3, p[2]
				movd mm4, p[3]
				paddb mm0, mm1
				paddb mm0, mm1
				paddb mm0, mm2
				paddb mm0, mm3
				paddb mm0, mm4
				movd eax, mm0
				mov c, eax
			}
#else
			sp = SumColors2(sp, p[0]);
			p[2] = SumColors2(p[2], p[3]);
			p[1] = SumColors2(p[1], p[2]);
			p[0] = SumColors2(p[0], p[1]);
			c = SumColors2(p[0], sp);
#endif
			// c = sp + p0 + p0 + p1 + p2 + p3

			PUTPIXEL(bmp, x,y, c);
		}
	}

	xphase = dx;

	StopProfiler(PROFILE_AVERAGETICK);
	//REPORT(180, AVERAGE_SCALE, AVERAGETICK, COLOR_BLUE);
}
