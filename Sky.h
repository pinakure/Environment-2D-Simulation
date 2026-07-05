#ifndef __SKY_H
#define __SKY_H

typedef struct s_skycontrol
{
	int foglevel;
	int fogcolor;
	int parallax;
	int blink;
	int luma;
}t_skycontrol;

void EFX_SkyInit(int foglevel, int fogcolor, int parallax);
void EFX_SkyDeinit(void);
void EFX_SkyTick(void);
void EFX_SkyDraw(void);

extern t_skycontrol SkyControl;

#endif