#ifndef __FIRE_H
#define __FIRE_H

typedef struct s_flame* FLAME;
typedef struct s_flame
{
	int x;
	int y;
	int w;
	int cw;
	int time;
	FLAME next;
}t_flame;

typedef struct s_flamecontrol
{	
	FLAME flames;
}t_flamecontrol;


extern t_flamecontrol FlameControl;

void EFX_FlameDestroy(void);
int EFX_FlamePreinit(void);

int EFX_FlameInit(int x, int y, int width, int life);
void EFX_FlameDeinit(void);
void EFX_FlameTick(void);
void EFX_FlameDraw(void);

#endif