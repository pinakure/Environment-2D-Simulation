#include "Common.h"

t_raincontrol RainControl;

static void DropInit(int i)
{
	RAINDROP r;
	int RND = GetRand();
	r = &RainControl.raindrops[i];
	
	//r->t  = SnowControl.chaos;//(rand()%n)*0.1f;
	if(RainControl.chaos>0)
	{
		r->x = INT2FIX(-60+(RND%(VWIDTH+60)));
	} else {
		r->x = INT2FIX(RND%(VWIDTH+60));
	}
	r->y = INT2FIX(-(RND%VHEIGHT));
	

	r->dy= RainControl.fallspeed;	
	r->dx= 100 + RainControl.chaos;
	
	r->mx = r->x;
	r->my = r->y;
	
	r->c = MAKECOL(60-(RND%30),125-(RND%50),133+(RND%32));//color
}
int EFX_RainInit(int drops, int fallspeed, int chaos)
{
	int i;

	if(drops > EFX_MAX_RAINDROPS)drops = EFX_MAX_RAINDROPS;
	RainControl.drops	  = drops;
	RainControl.fallspeed = fallspeed;
	RainControl.chaos	  = chaos;
	RainControl.raindrops = NULL;	
	RainControl.raindrops = malloc(sizeof(t_drop)*drops);
	if(!RainControl.raindrops)return false;
	
	for(i=0;i<drops;i++)
	{
		DropInit(i);
	}
	
	EnvControl.rain = true;
	return true;
}

void EFX_RainDeinit(void)
{
	if(RainControl.raindrops)free(RainControl.raindrops);
	RainControl.raindrops = NULL;
	EnvControl.rain = false;	
}

void EFX_RainDraw(void)
{
	RAINDROP r;

	int i;
		
	for(i=0;i<RainControl.drops;i++)
	{
		r = &RainControl.raindrops[i];
		
		line(EFXFade, FIX2INT(r->x), FIX2INT(r->y), FIX2INT(r->mx), FIX2INT(r->my), r->c);
		r->mx = r->x;
		r->my = r->y;
		
		/*r->mx = r->x;
		r->my = r->y;
		line(EFXFade, r->mx, r->my, r->mx-1, r->my-3, r->c);*/
		//if(getpixel(EFXBuffer, r->x, r->y)==COLOR_RED)DropInit(i);
	}	
}

void EFX_RainTick(void)
{
	RAINDROP r;
	int i;
	
	StartProfiler(PROFILE_RAINTICK);
	
	r = RainControl.raindrops;
		
	for(i=0;i<RainControl.drops;i++)
	{		
		r->x += r->dx;
		r->y += r->dy;

		if(r->x > INT2FIX(VWIDTH-1))
		{
			r->mx-=INT2FIX(VWIDTH-1);
			r->x=0;
		} else
		if(r->x < 0)
		{
			r->mx+=INT2FIX(VWIDTH-1);
			r->x=INT2FIX(VWIDTH-1);
		}

		if(r->y > INT2FIX(VHEIGHT))DropInit(i);//->y-=INT2FIX(VHEIGHT+10);
		r++;
	}
	
	StopProfiler(PROFILE_RAINTICK);
	//REPORT(170,  RAIN_SCALE, RAINTICK___, COLOR_PURPLE);
}




