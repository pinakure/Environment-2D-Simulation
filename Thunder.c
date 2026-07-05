#include "Common.h"

typedef struct s_ray* THUNDER;
typedef struct s_ray
{
	int x;
	int y;
	int visible;
	int w;
	int h;
	int time;
	int timer;
	int flash;
	int flamex;
	int flamey;
	BITMAP *surface;
}t_ray;

typedef struct s_thundercontrol
{
	int rays;//number of thunders
	int frequency;
	int lifetime; //life of a ray
	int spread;
	THUNDER thunders;
}t_thundercontrol;


t_thundercontrol ThunderControl;

BITMAP *ThunderTemplate[16];



void RayDestroy(int i)
{
	THUNDER t;
	t = &ThunderControl.thunders[i];
	if(t)
	{	
		if(t->surface)destroy_bitmap(t->surface);
		t->surface=NULL;
	}
}


void RayRender(THUNDER t)
{
	int RND = GetRand();
	int x, y, l;
	int a;
	int tx, ty; //temporal nodes	

	int lx=0, ly=0;

	x = t->w>>1;
	y = 0;

	l = 0;

	tx = x;
	ty = y;

	if(x<0)x=0;
	if(y<0)y=0;
	if(x>t->surface->w)x=t->surface->w-2;
	
	a = 73+(RND&127);
		
	while(l < ThunderControl.lifetime)
	{
		RND = GetRand3();

		if(y<t->surface->h)
		PUTPIXEL(t->surface, x, y, MAKECOL(a, a, a+55));
		
		if(l%ThunderControl.spread < ThunderControl.spread>>3)
		{
			tx=x;
			ty=y;
		} else {
			if(l%ThunderControl.spread==ThunderControl.spread-1)
			{	
				x = tx;
				y = ty;				
			}			
		}
		
		if(y>t->flamey)
		{
			t->flamex=x;
			t->flamey=y;
		}
		y++;
		
		x+=(RND)-1;
		if(x==t->w)x-=2;
		if(x<0)x+=2;
		l+=RND;		
	}	
}

void RayCreate(int i)
{
	THUNDER t;
	int RND = GetRand();
	
	t = &ThunderControl.thunders[i];

	t->h = 113+(RND&127);
	t->w = 16+(RND&31);
	t->x = RND%VWIDTH;
	t->y = 0;
	t->timer = 0;
	t->time = 30+(RND&127);
	t->flash=RND&1;
	//t->flamex = 0;
	//t->flamey = 0;
	t->visible=0;	
}



int EFX_ThunderInit(int thunders, int lifetime, int frequency, int spread)
{
	THUNDER t;
	int i;
	
	if(thunders>EFX_MAX_THUNDERS)thunders = EFX_MAX_THUNDERS;
	
	ThunderControl.rays = thunders;
	ThunderControl.lifetime = lifetime;
	if(!frequency)frequency+=10;
	ThunderControl.frequency = frequency;
	ThunderControl.spread = spread;
	
	ThunderControl.thunders = NULL;
	ThunderControl.thunders = malloc(sizeof(t_ray)*thunders);
	if(!ThunderControl.thunders)return 0;
	
	for(i=0; i<thunders; i++)
	{		
		ThunderControl.thunders[i].surface=NULL;
		RayCreate(i);
		
		t = &ThunderControl.thunders[i];
		if(t)
		{		
			if(t->surface)
			{
				destroy_bitmap(t->surface);
			}
			t->surface = create_bitmap(t->w, t->h);
			clear_to_color(t->surface, COLOR_PINK);
			RayRender(t);
		}
	}	
	EnvControl.thunders = true; 
	return 1;
}

void EFX_ThunderDeinit(void)
{
	int i;
	if(ThunderControl.thunders)
	{
		for(i=0; i<ThunderControl.rays; i++)
		{		
			RayDestroy(i);			
		}		
	}
	free(ThunderControl.thunders);
	ThunderControl.thunders = NULL;
	EnvControl.thunders = false;
}

void EFX_ThunderDraw(void)
{
	THUNDER t;
	int i;

	for(i=0;i<ThunderControl.rays;i++)
	{
		t = &ThunderControl.thunders[i];
		if(t->visible)
		{
			if(t->visible==1)if(t->flash)
			{
				SkyControl.luma=255;
				clear_to_color(EFXFade, COLOR_WHITE);
			}
			masked_blit(t->surface, EFXFade, 0, 0, t->x, 0, t->w, t->h);
			t->visible--;
		}
	}		
}

void EFX_ThunderTick(void)
{
	THUNDER t;
	int i;
	int RND;
	
	StartProfiler(PROFILE_THUNDERTICK);
	
	for(i=0;i<ThunderControl.rays;i++)
	{
		t = &ThunderControl.thunders[i];
		t->timer++;
		t->time--;
		
		//t->visible = false;
		//if((t->timer%ThunderControl.frequency)==ThunderControl.frequency-1)
		
		if(t->timer+1==ThunderControl.frequency)
		{
			RND = GetRand();		
			t->timer = 0;
			t->visible = RND&63;
			if(!t->flash)
			{
				if(t->flamey>200)
				{
					EFX_FlameInit(t->x+t->flamex, t->flamey, 4+(RND&7), 60+(RND&255));
				}
			}
		}
		if(t->time<0)
		{
			RayCreate(i);
		}
	}
	
	StopProfiler(PROFILE_THUNDERTICK);
	//REPORT(140,  THUNDER_SCALE, THUNDERTICK, COLOR_YELLOW);	
}
