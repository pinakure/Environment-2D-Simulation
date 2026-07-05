#include "Common.h"	

int main(void)
{
	int Execute, EngineOldTick= 0;
	
	allegro_init();
	Execute = Init();
	if(!Execute)return 1;

	Execute = EnviromentInit();
	if(!Execute)
	{
		Deinit();
		return 1;
	}

	while(Execute)
	{
		/* MAIN LOOP */


		MouseX = mouse_x;
		MouseY = mouse_y;
		
		if(EngineOldTick != EngineTicks)
		{
			/* LOGIC */
			EngineOldTick = EngineTicks;			
			
			if(key[KEY_ESC])Execute = 0;

			EnviromentTick();		/*  <------------------------ */
		}

		/* DRAW */
		VideoSwitchPage();
		
		EnviromentDraw();			/*  <------------------------ */

		TickProfiler();		
		VideoDrawFrame();
		
		//vsync();			
	}		
	EnviromentDeinit();
	Deinit();	
	return 0;
}
END_OF_MAIN()

