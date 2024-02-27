#include "stm32f4xx.h"

#define B0(data,x) data&=~(1<<x)
#define B1(data,x) data|=(1<<x)

#define B00(data,x) data&=~(3<<2*x)
#define B01(data,x) data=data&~(3<<2*x)|(1<<2*x)
#define B10(data,x) data=data&~(3<<2*x)|(2<<2*x)
#define B11(data,x) data|=(3<<2*x)

#define B0000(data,x) data&=~(15<<4*x)
#define B0111(data,x) data=data&~(15<<4*x)|(7<<4*x)

#define R1(data,x) (data&1<<x)
