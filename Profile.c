// M4GEEK - Runtime Profiler
// All rights Reserved, 2012
// Written by Mitikoro and Offsetzero
#include "Common.h"

static char* ProfileNames[]={
	#define M(a)		#a,
	#include "ProfileNames.h"
	#undef M	
};

t_profilercontrol Profiler;

/*__declspec(naked) long GetCycles(void)
{
	__asm{
		rdtsc
		ret
	}
}*/

static inline unsigned long long
GetCycles(void)
{
	unsigned int low, high;

	__asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high) : :);
	return low | ((unsigned long long)high << 32);
}

void InitProfiler(unsigned int max_entries)
{
	int i;

	Profiler.count = max_entries;

	Profiler.entry = malloc(sizeof(t_profileentry)*max_entries);

	for(i=0; i<Profiler.count; i++)
	{
		Profiler.entry[i].avg=0;
		Profiler.entry[i].peak=0;
		Profiler.entry[i].value=0;
		Profiler.entry[i].clock=0;
		Profiler.entry[i].color=makecol(64*(rand()%4),255, 64*(rand()%4));
		if(i==PROFILE_AVERAGETICK)Profiler.entry[i].scale=13;
		else Profiler.entry[i].scale=9;
		Profiler.entry[i].name = ProfileNames[i];
	}	
}

void DeinitProfiler(void)
{
	free(Profiler.entry);
	Profiler.count=0;
}

void StartProfiler(enum E_ProfileNames index)
{
	Profiler.entry[index].value = -GetCycles();
}

void StopProfiler(enum E_ProfileNames index)
{
	Profiler.entry[index].value += GetCycles();	
}

void TickProfiler(void)
{
	PROFILE p;
	int i, c;

	if(EngineDrawFPS)ProfileClear();
	for(i=0; i<Profiler.count; i++)
	{
		p = &Profiler.entry[i];
		

		p -> avg = (p->value+p ->avg)>>1;
		
		if( p->value > p->peak )
		{
			c = COLOR_RED;
			p -> peak = p->value;
		}
		
	}
}

void DrawProfiler(void)
{
	PROFILE p;
	int i, c;

	if(EngineDrawFPS)ProfileClear();
	for(i=0; i<Profiler.count; i++)
	{
		p = &Profiler.entry[i];

		if( p->value > p->peak )
		{
			c = COLOR_RED;
		} else {
			c = COLOR_YELLOW;
		}

		textprintf_ex(VBuffer, font, 0, i*10, 
							p->color, -1, 
							"[%11s:%8u/%8u]", p->name, p->peak, p->avg);
		line(EFXFade, 155,	(i*10)+p->clock, 
							155+((unsigned)(p->avg)>>p->scale), (i*10)+p->clock, 
							p->color); 
		//putpixel(EFXFade, 155+((unsigned)(p->avg)>>p->scale), (i*10)+p->clock, p->color); 
		/*line(VBuffer, 156+((unsigned)(p->avg)>>p->scale),(i*10)+(p->clock%10),
							VWIDTH, (i*10)+(p->clock%10), 
							COLOR_PINK); */
		p->clock++;	
		p->clock&=7;
	}
}
void ProfileClear(void)
{
	int i;

	for(i=0; i<Profiler.count; i++)
	{
		Profiler.entry[i].peak=0;
	}
}			
