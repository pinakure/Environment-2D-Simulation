#ifndef __SNOW_H
#define __SNOW_H

#pragma pack(push, 1)

typedef struct s_flake* SNOWFLAKE;
typedef struct s_flake
{
	int cx;		// 0 //capture memo vars
	int cy;		// 4
	int cc;		// 8

	int c;		// c

	int ox;		// 10
	int oy;		// 14

	fix x;		// 18
	fix y;		// 1c
	
	int t;		// 20 //tendence	
}t_flake;

#pragma pack(pop)

typedef struct s_snowcontrol
{
	int flakes;	     //number of flakes
	//float fallspeed; //falling speed
	//float chaos;	 //trajectory distortion
	int fallspeed; //falling speed
	int chaos;	 //trajectory distortion
	SNOWFLAKE snowflakes;
}t_snowcontrol;

//int EFX_SnowInit(int flakes, float fallspeed, float chaos);
int EFX_SnowInit(int flakes, int fallspeed, int chaos);
void EFX_SnowDeinit(void);
void EFX_SnowDraw(void);
void EFX_SnowTick(void);

#endif