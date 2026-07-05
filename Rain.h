#ifndef __RAIN_H
#define __RAIN_H

typedef struct s_drop* RAINDROP;
typedef struct s_drop
{
	fix x;
	fix y;
	int c;
	int mx;
	int my;
	int dx;
	int dy;
}t_drop;

typedef struct s_raincontrol
{
	int drops;	     //number of raindrop
	//float fallspeed; //falling speed
	//float chaos;	 //trajectory distortion
	int fallspeed; //falling speed
	int chaos;	 //trajectory distortion
	RAINDROP raindrops;
}t_raincontrol;

//int EFX_RainInit(int flakes, float fallspeed, float chaos);
int EFX_RainInit(int flakes, int fallspeed, int chaos);
void EFX_RainDeinit(void);
void EFX_RainDraw(void);
void EFX_RainTick(void);

#endif