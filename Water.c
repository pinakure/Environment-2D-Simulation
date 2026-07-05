#include "Common.h"

int EFX_WaterInit(void)
{
	return 0;	
}

void EFX_WaterDeinit(void)
{
	
}

void EFX_WaterTick(void)
{
	StartProfiler(PROFILE_WATERTICK);

	StopProfiler(PROFILE_WATERTICK);
	//REPORT(90,FIRE_SCALE,WATERTICK__,COLOR_YELLOW);
}

void EFX_WaterDraw(void)
{
	
}
