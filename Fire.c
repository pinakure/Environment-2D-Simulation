#include "Common.h"

t_flamecontrol FlameControl;

BITMAP *FlameBitmap[12];


void EFX_FlameDestroy(void)
{
	int i;
	for(i=0; i<12; i++)
	{
		destroy_bitmap(FlameBitmap[i]);		
	}
}
int EFX_FlamePreinit(void)
{
	int i;
	BITMAP *b=0;
	
#ifdef LINUX
	b = load_bitmap("./fx_flame.bmp", NULL);
#else
	b = load_bitmap(".\\fx_flame.bmp", NULL);
#endif
	
	if(!b)return 1;
	
	for(i=0; i<12; i++)
	{
		FlameBitmap[i]=create_bitmap(8, 16);
		stretch_blit(b, FlameBitmap[i], i*16, 0, 16, 32, 0, 0, 8, 16);		
	}
	
	return 0;
}

int EFX_FlameInit(int x, int y, int width, int life)
{	
	FLAME f=NULL;
	FLAME tf;

	f = malloc(sizeof(t_flame));
	if(!f)return 0;
	
	f->x = x;
	f->y = y;
	f->cw=0.5f;
	f->w = width;
	f->next = NULL;
	f->time = life;
	
	
	if(!FlameControl.flames)
	{
		FlameControl.flames=f;
	} else {
		tf = FlameControl.flames;
		while(tf->next)
		{
			tf=tf->next;
		}
		tf->next = f;		
	}
		
	EnvControl.fire=true;
	return 1;
}

void EFX_FlameDeinit(void)
{
	FLAME f;
	FLAME n;
	f = FlameControl.flames;

	while(f)
	{
		n = f->next;
		free(f);
		f=n;
	}
	
	EnvControl.fire=false;
}



void EFX_FlameDraw(void)
{
	int c, x, y, v, w;
	int frame;
	FLAME f;

	int C[4];

	StartProfiler(PROFILE_FIREDRAW);

	f = FlameControl.flames;
	
	while(f)
	{
		if(!(f->time%3))
		{
			frame = (f->time>>1)%12;
			x = f->x-(FlameBitmap[frame]->w>>1);
			y = f->y-(FlameBitmap[frame]->h);	
			masked_blit(FlameBitmap[frame], EFXFade, 
						0, 0, 
						x, y,
						FlameBitmap[frame]->w, FlameBitmap[frame]->h);
		}
		f=f->next;
	}

	StopProfiler(PROFILE_FIREDRAW);
	//REPORT(100,FIRE_SCALE,FIREDRAW___,COLOR_ORANGE);
}

void EFX_FlameTick(void)
{
	FLAME f;
	FLAME pf=NULL;//previous
	
	StartProfiler(PROFILE_FIRETICK);

	f = FlameControl.flames;
	
	while(f)
	{
		if(!(f->time%25))
		{
			EFX_SmokeInit(f->x+((GetRand()%6)-3), f->y, 50, 100);
		}

		f->time--;
		
		if(f->x>VWIDTH-f->w)f->x=VWIDTH-f->w;
		if(f->y>VHEIGHT-2)f->y=VHEIGHT-2;
		if(f->x<f->w)f->x=f->w;
		if(f->y<0)f->y=0;
	
		if(!f->time)
		{
			if(pf)
			{
				pf->next = f->next;
				free(f);
				f=pf->next;
			} else {
				FlameControl.flames = f->next;
				free(f);
				f = FlameControl.flames;				
			}			
			continue;
		} else {
			pf = f;
			f=f->next;
		}		
	}
	
	StopProfiler(PROFILE_FIRETICK);
	//REPORT(150,FIRE_SCALE, FIRETICK___, COLOR_ORANGE);	
}
