#include "Common.h"

t_skycontrol SkyControl;

static void SkyPreRender(void)
{
	int i, ii, v;
		
	for(i=0; i<VHEIGHT; i++)
	{	
		ii = VHEIGHT-i;
		

		v = (((i%(16))+(ii%400)))>>3;
		line(EFXSky, 0, i, VWIDTH, i, MAKECOL(v>>2, v, v));
	}	
}

void EFX_SkyInit(int foglevel, int fogcolor, int parallax)
{
	SkyControl.blink=false;
	SkyControl.fogcolor=fogcolor;
	SkyControl.parallax=parallax;
	SkyControl.luma = 0;

	SkyPreRender();
}

void EFX_SkyDeinit(void)
{
	
}

void EFX_SkyDraw(void)
{	
	StartProfiler(PROFILE_SKYDRAW);
	
	if(SkyControl.luma>1)
	{
		EnvControl.quake=true;
		SkyPreRender();
	} else {
		if(SkyControl.luma!=0)
		{
			EnvControl.quake=false;
			SkyControl.luma=0;
			SkyPreRender();
		}
	}
	
	StopProfiler(PROFILE_SKYDRAW);
	//REPORT(110,SAME_SCALE,SKYDRAW____,COLOR_BLUE);
}

void EFX_SkyTick(void)
{	
	StartProfiler(PROFILE_RAINTICK);
	
	if(SkyControl.luma>0)
	{
		SkyControl.luma-=48;
	} else {
		SkyControl.luma=0;
	}
	
	StopProfiler(PROFILE_RAINTICK);
	//REPORT(120,SAME_SCALE,SKYTICK____,COLOR_BLUE);
}
