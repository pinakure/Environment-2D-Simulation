#include "Common.h"

t_snowcontrol SnowControl;


void FlakePreinit(int i)
{
	SNOWFLAKE s;
	int RND = rand();
	s = &SnowControl.snowflakes[i];
	
	
	if(SnowControl.chaos>0)
	{
		//s->ox = (-160-SnowControl.chaos)+(RND&511);
		//s->oy = -(RND&255);
		s->ox = -100+(RND%(VWIDTH+100));
		s->t  = SnowControl.chaos+((RND%10)*20);//(rand()%n)*0.1f;	
	} else {
		s->ox = RND%(VWIDTH+200);
		s->t  = -(SnowControl.chaos+((RND%10)*20));
	}
	s->oy = -(RND%VHEIGHT);
	
	s->c = 120+(rand()%80);	
	s->c = makewhite(s->c);
}


void FlakeInit(int i)
{
	SNOWFLAKE s;
	int RND = GetRand();

	s = &SnowControl.snowflakes[i];

	
	s->x  = INT2FIX(s->ox);
	s->y  = INT2FIX(s->oy);
}

int EFX_SnowInit(int flakes, int fallspeed, int chaos)
{
	int i;

	if(flakes > EFX_MAX_SNOWFLAKES)flakes = EFX_MAX_SNOWFLAKES;
	SnowControl.flakes	  = flakes;
	SnowControl.fallspeed = fallspeed;
	SnowControl.chaos	  = chaos;
	SnowControl.snowflakes= NULL;	
	SnowControl.snowflakes= malloc(sizeof(t_flake)*flakes);
	if(!SnowControl.snowflakes)return false;
	
	for(i=0;i<flakes;i++)
	{
		FlakePreinit(i);
		FlakeInit(i);	
	}
	
	EnvControl.snow = true;
	return true;
}

void EFX_SnowDeinit(void)
{
	if(SnowControl.snowflakes)free(SnowControl.snowflakes);
	SnowControl.snowflakes = NULL;
	EnvControl.snow = false;	
}

void EFX_SnowDraw(void)
{
	SNOWFLAKE s;

	int i,x,y;
			
	for(i=0;i<SnowControl.flakes;i++)
	{
		s = &SnowControl.snowflakes[i];

		x = FIX2INT(s->x);
		y = FIX2INT(s->y);
		if(y>0)
		if(x>0)
		{
			s->cc = getpixel(EFXBuffer, x, y);
		
			if(s->cc!=COLOR_PINK)
			if(s->cc!=COLOR_WHITE)
			{
				putpixel(EFXBuffer, s->cx, s->cy, COLOR_WHITE);
				FlakeInit(i);
				continue;
			}
		}
		s->cx=x;
		s->cy=y;
		putpixel(EFXClear, s->cx, s->cy, s->c);		
	}
	//masked_blit(EFXClear, VBuffer, 0, 0, 0, 0, EFXBitmap->w, EFXBitmap->h);
	//clear_to_color(EFXClear, COLOR_PINK);
}

//__declspec(naked) void __fastcall UpdateFlake(SNOWFLAKE s, int rnd)
void UpdateFlake(SNOWFLAKE s, int rnd)
{

		if(rnd&1)
		{
			s->x += s->t + SnowControl.chaos;
		}
		s->y += SnowControl.fallspeed+(rnd&127);

		if((s->x > INT2FIX(VWIDTH-1))) s->x=0;
		if((s->x < 0)) s->x=INT2FIX(VWIDTH-1);

		if((s->y > INT2FIX(VHEIGHT-1)))
			s->y-=(INT2FIX(VHEIGHT));

//	__asm {
//		push ebp
//		mov ebp, ecx
//
//		and edx, 0x7F
//
//		mov ecx, dword ptr [ebp + 0x1C]		// ECX=y
//		add ecx, SnowControl.fallspeed
//		add ecx, edx
//
//		mov eax, dword ptr [ebp + 0x18]		// EAX=x
//		test dl, 1
//		jz Over
//		add eax, dword ptr [ebp + 0x20]		// EAX=x+t
//		add eax, SnowControl.chaos			// EAX=x+t+chaos
//Over:
//		// EAX=x, ECX=y
//		cmp eax, INT2FIX(VWIDTH-1)
//		ja Over2
//		xor eax, eax
//Over2:
//		cmp eax, 0
//		jb Over3
//		mov eax, INT2FIX(VWIDTH-1)
//Over3:
//
//		cmp ecx, INT2FIX(VHEIGHT-1)
//		ja Over4
//		sub ecx, INT2FIX(VHEIGHT)
//Over4:
//
//		mov dword ptr [ebp + 0x18], eax
//		mov dword ptr [ebp + 0x1C], ecx
//
//		pop ebp
//		ret
//	}
}

//#define ASM

void EFX_SnowTick(void)
{
	SNOWFLAKE s;
	int i;
	int RND;
	
	StartProfiler(PROFILE_SNOWTICK);

	s = SnowControl.snowflakes;

	for(i=0;i<SnowControl.flakes;i++)
	{
		RND=GetRand();
//#ifdef ASM
		//UpdateFlake(s, RND);
//#else
		if(RND&1)
		{
			s->x += s->t + SnowControl.chaos;
		}
		s->y += SnowControl.fallspeed+(RND&127);

		if((s->x > INT2FIX(VWIDTH-1))) s->x=0;
		if((s->x < 0)) s->x=INT2FIX(VWIDTH-1);

		if((s->y > INT2FIX(VHEIGHT-1)))
			s->y-=(INT2FIX(VHEIGHT));
//#endif
		s++;
	}

	StopProfiler(PROFILE_SNOWTICK);
	//REPORT(160,  SNOW_SCALE, SNOWTICK___, COLOR_GREEN);
}
