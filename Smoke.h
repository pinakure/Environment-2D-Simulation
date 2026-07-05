#ifndef __SMOKE_H
#define __SMOKE_H

typedef struct s_smokepart* SMOKEPART;
typedef struct s_smokepart
{
	int x;
	int y;
	int c;
	int f;
	int time;
	int life;
}t_smokepart;

typedef struct s_smokesys* SMOKESYSTEM;
typedef struct s_smokesys
{
	int x;
	int y;
	int life;
	int variation;//random value
	int count;
	SMOKEPART smokepart;
	SMOKESYSTEM prev;
	SMOKESYSTEM next;
}t_smokesys;

typedef struct s_smokecontrol
{	
	int spread; //how much the particles will spread after spawning
	SMOKESYSTEM smokesys;
}t_smokecontrol;

void EFX_SmokePreinit(void);
void EFX_SmokeInit(int x, int y, int life, int variation);
void EFX_SmokeTick(void);
void EFX_SmokeDraw(void);

#endif