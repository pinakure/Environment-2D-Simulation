#include "Common.h"

t_envcontrol EnvControl;
BITMAP *EFXBuffer=NULL;
BITMAP *EFXClear=NULL;
BITMAP *EFXFade=NULL;
BITMAP *EFXSky=NULL;

void EnviromentDraw(void)
{	
	EFX_SkyDraw();
	EFX_SnowDraw();
	EFX_ThunderDraw();
	EFX_SmokeDraw();
	EFX_FlameDraw();
	EFX_RainDraw();
	EFX_WaterDraw();
	
	
//	clear_to_color(EFXBitmap, makecol(255,0,255));
}

void EnviromentTick(void)
{
	EFX_SkyTick();
	EFX_ThunderTick();
	EFX_FlameTick();
	EFX_SmokeTick();
	EFX_SnowTick();
	EFX_RainTick();
	EFX_WaterTick();
}

int EnviromentInit(void)
{
	//Initialize Enviromental resources
	EFXBuffer = create_bitmap(VWIDTH,VHEIGHT);
	if(!EFXBuffer)return 0;
	clear_to_color(EFXBuffer, COLOR_PINK);
	
	EFXClear = create_bitmap(VWIDTH,VHEIGHT);
	if(!EFXClear)return 0;
	clear_to_color(EFXClear, COLOR_PINK);
	
	EFXFade = create_bitmap(VWIDTH,VHEIGHT);
	if(!EFXFade)return 0;
	clear_to_color(EFXFade, COLOR_PINK);

	EFXSky = create_bitmap(VWIDTH,VHEIGHT);
	if(!EFXSky)return 0;
	clear_to_color(EFXSky, 0);

	EnvControl.bubbles=false;
	EnvControl.fire=false;
	EnvControl.fog=false;
	EnvControl.quake=false;
	EnvControl.rain=false;
	EnvControl.skyblink=false;
	EnvControl.smoke=false;
	EnvControl.snow=false;
	EnvControl.thunders=false;
	EnvControl.water=false;
	
	EFX_SkyInit(0, 0, 0);
	EFX_FlamePreinit();
	EFX_SmokePreinit();
	EFX_WaterInit();	

	if(!EFX_ThunderInit(8, 600, 100, 32))return 0;
	if(!EFX_SnowInit(200, 200, 200))return 0;
	if(!EFX_RainInit(25, 0x7ff, 200))return 0;
	
	return 1;
}

void EnviromentDeinit(void)	//Deinitialize Enviromental resources
{
	EFX_RainDeinit();
	EFX_SnowDeinit();
	EFX_FlameDeinit();
	EFX_ThunderDeinit();
	EFX_SkyDeinit();

	EFX_FlameDestroy();
	EFX_WaterDeinit();

	destroy_bitmap(EFXBuffer);
	destroy_bitmap(EFXClear);
	destroy_bitmap(EFXFade);	
	destroy_bitmap(EFXSky);
}
