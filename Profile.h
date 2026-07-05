// M4GEEK - Runtime Profiler
// All rights Reserved, 2012
// Written by Mitikoro and Offsetzero
// Header file.
#ifndef __PROFILE_H
#define __PROFILE_H

typedef struct s_profileentry* PROFILE;
typedef struct s_profileentry
{
	int peak;
	int avg;
	int value;
	int scale;
	int color;
	int clock;
	char *name;
}t_profileentry;

typedef struct s_profilercontrol
{
	int count;
	PROFILE entry;
}t_profilercontrol;

enum E_ProfileNames
{
	#define M(a)		PROFILE_##a,
	#include "ProfileNames.h"
	#undef M
	PROFILE_MAX
};

void StartProfiler(enum E_ProfileNames index);
void StopProfiler(enum E_ProfileNames index);
void ProfileClear(void);
void DrawProfiler(void);
void TickProfiler(void);
void DeinitProfiler(void);
void InitProfiler(unsigned int max_entries);	
// long GetCycles(void);

#endif