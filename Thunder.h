#ifndef __THUNDER_H
#define __THUNDER_H


int EFX_ThunderInit(int thunders, int lifetime, int frequency, int spread);
void EFX_ThunderDeinit(void);
void EFX_ThunderDraw(void);
void EFX_ThunderTick(void);


#endif