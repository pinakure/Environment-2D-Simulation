#ifndef __FIXED_H
#define __FIXED_H

typedef long fix;
#define FIX_N		8

#define INT2FIX(i)  ((i) << FIX_N)
#define INT_DEC_2FIX(i,d)  (((i) << FIX_N) + (d))
#define FIX2INT(f)	((f) >> FIX_N)

//
// fixed_t a, b;
// a = -((long)0x280);
// c = a+b
//


#endif