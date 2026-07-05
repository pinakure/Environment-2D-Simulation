/*
Common.c: M4GeekTech common routine kit 
*/
#include "Common.h"

int MouseX, MouseY;

/* TIMER FUNCTION */
volatile 
unsigned int	EngineFrames = 0,
				EngineFPS	 = 1,
				EnginePeakFPS= 0,
				EngineDrive	 = 0,
				EngineDrawFPS= 0,
				EngineTicks  = 1;
				
int RND[256];
int RND3[256];

int GetRand3(void)
{
	static int index=0;	
	
	index++;
	index&=0xFF;

	return RND3[index];
}

int GetRand(void)
{
	static int index=0;	
	
	index++;
	index&=0xFF;

	return RND[index];
}

void RandInit(void)
{
	int i=0;

	srand(time(NULL));
	
	while(i<256)
	{
		RND[i] = rand();
		RND3[i] = rand()%3;
		i++;
	}
}

static void EngineTicker(void)
{
	EngineTicks++;

	if((EngineTicks%FPS)==0) {
		EngineFPS = EngineFrames;
		EngineFrames = 0;
		EngineDrawFPS=1;
		if(EngineFPS > EnginePeakFPS) EnginePeakFPS = EngineFPS;
	}
}
END_OF_STATIC_FUNCTION(EngineTicker);
/* END OF TIMER FUNCTION */


char *GetStaticChar1024(void)
{
	static char str[4096];

	str[0] = 0;
	return str;
}

int Init(void){	
	RandInit();
	install_keyboard();
	install_mouse();
	install_timer();
	if(!VideoInit()) {		
		return 1;
	}
	show_mouse(screen);
	
	install_int_ex(EngineTicker, BPS_TO_TIMER(FPS));
	
#ifdef LINUX
	//font=load_bitmap_font("/home/offsetzero/m4g/N/gfx/system/f_hud.bmp", NULL, NULL);
#else
	//font=load_bitmap_font("C:\\DEV\\N\\src\\N_Enviroment\\font.bmp", NULL, NULL);
#endif

	InitProfiler(PROFILE_MAX);
	return 1;
}

void Deinit(void)
{
	remove_int(EngineTicker);
	DeinitProfiler();
	VideoDeinit();	
}

