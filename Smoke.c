#include "Common.h"

t_smokecontrol SmokeControl;

#define EFX_SMOKE_MAXPOS	64

static int SmokePos[EFX_SMOKE_MAXPOS*2];
static int SmokePosIndex=0;

void EFX_SmokePreinit(void)
{
	int i, ii;
	SmokeControl.spread=1;
	SmokeControl.smokesys=NULL;

	for(i=0; i<EFX_SMOKE_MAXPOS*2; i++)
	{
		ii = EFX_SMOKE_MAXPOS*2-i;
		SmokePos[i] = sin(ii)*2+((rand()&1)*3);
	}
}

SMOKESYSTEM SmokeCreate(int x, int y, int life, int variation)
{
	SMOKESYSTEM s;
	SMOKEPART p;
	int i;

/* Create particle system */
	s = malloc(sizeof(t_smokesys));
	if(!s)return NULL;
	
	s->x = x;
	s->y = y;
	s->life = life<<1;
	s->variation = variation;
	s->count = EFX_MAX_SMOKEPARTS;
	s->smokepart = NULL;
	s->next = NULL;
	s->prev = NULL;

/* Create p.system's particles */
	s->smokepart = malloc(sizeof(t_smokepart)*s->count);
	if(!s->smokepart)return NULL;

	for(i=0; i<EFX_MAX_SMOKEPARTS; i++)
	{
		p = &s->smokepart[i];
		p->x	= x;
		p->y	= y;		
		p->time = life;//variate this
		p->c = COLOR_WHITE;
		p->f = 0;
		p->life=0;
	}
	return s;
}


static SMOKESYSTEM GetLastSmokeSystem(void)
{
	SMOKESYSTEM s;
	
	s = SmokeControl.smokesys;
	if(!s)return NULL;
	while(s->next)
	{		
		s = s->next;
	}
	return s;
}

void SmokeDeinit(SMOKESYSTEM s)
{
	ASSERT(s);

	if(s->prev)s->prev->next=s->next;
	else SmokeControl.smokesys = s->next;
	if(s->next)s->next->prev=s->prev;

	free(s->smokepart);
	free(s);
}

void EFX_SmokeInit(int x, int y, int life, int variation)
{	
	SMOKESYSTEM s;

	s = GetLastSmokeSystem();

	if(!s)
	{		
		SmokeControl.smokesys = SmokeCreate(x, y, life, variation);
		SmokeControl.smokesys->prev=s;
	} else {
		s->next = SmokeCreate(x, y, life, variation);
		s->next->prev=s;
	}	
}

void EFX_SmokeTick(void)
{
	SMOKESYSTEM ks;
	SMOKESYSTEM s;
	SMOKEPART p;
	int i, v;
	static int phasey=0;
	int c;

	StartProfiler(PROFILE_SMOKETICK);
	
	s = SmokeControl.smokesys;

	phasey^=1;

	while(s)
	{
		if(phasey)s->y--;
		
		for(i=0; i < s->count; i++)//Count system's particles
		{
			p = &s->smokepart[i];
			v = SmokePos[p->f&(EFX_SMOKE_MAXPOS-1) + (i%EFX_SMOKE_MAXPOS+(i%EFX_SMOKE_MAXPOS))];
			
			p->f--;
			
			if(phasey)
			{	
				p->y = s->y-(i);
				p->y+=phasey;
			} else {
				p->y = s->y-(i);
			}
						
			p->y -=(p->time&3);// /100
			p->x = s->x + v;
			
			c = 255 - p->time;
			if(c<16)c=0;
			p->c = SumColors(makewhite(c), (getpixel(EFXFade, p->x, p->y)));
			//if(p->c<=10)p->c=COLOR_PINK;

			p->time++;			
		}
		
		s->life--;
		if(s->life<=0)
		{
			ks = s;
			s = s->next;
			SmokeDeinit(ks);				
		} else {	
			s = s->next;
		}
	}

	StopProfiler(PROFILE_SMOKETICK);
	//REPORT(130, SMOKE_SCALE, SMOKETICK__, COLOR_RED);
}


void EFX_SmokeDraw(void)
{	
	SMOKESYSTEM s;
	SMOKEPART p;
	int i;

	s = SmokeControl.smokesys;

	while(s)
	{
		for(i=0; i < s->count; i++)//Count system's particles
		{
			p = &s->smokepart[i];
			if(p->x>0)if(p->y>0)
			if(p->x<VWIDTH-1)if(p->y<VHEIGHT-1)
			{
				p->c = SumColors(p->c, getpixel(EFXFade, p->x, p->y));//!!!!!!
				PUTPIXEL(EFXFade, p->x, p->y, p->c);
				if(i==0)if(GetRand()&1)PUTPIXEL(EFXFade, p->x, p->y, 0);
			}
		}
		s = s->next;
	}
}
