#ifndef __ENVIROMENT_H
#define __ENVIROMENT_H

#define EFX_MAX_SNOWFLAKES		4000
#define EFX_MAX_RAINDROPS		800
#define EFX_MAX_THUNDERS		40000
#define EFX_MAX_SMOKEPARTS		32

typedef struct s_envcontrol
{
	int snow;
	int fire;
	int thunders;
	int rain;
	int quake;
	int fog;
	int smoke;
	int water;
	int bubbles;
	int skyblink;
}t_envcontrol;


#include "Sky.h"
#include "Snow.h"
#include "Rain.h"
#include "Thunder.h"
#include "Fire.h"
#include "Smoke.h"
#include "Water.h"		//warp fx

//#include "Fog.h"			//only on sky

//#include "Bubbles.h"		//only on water

void EnviromentDraw(void);
void EnviromentTick(void);
int EnviromentInit(void);
void EnviromentDeinit(void);

extern t_envcontrol EnvControl;
extern BITMAP *EFXBuffer;
extern BITMAP *EFXClear;
extern BITMAP *EFXFade;
extern BITMAP *EFXSky;

#endif
