#include "pre.h"

void IWDG_Init(u8 pr,u16 rlr)
{
	IWDG->KR = 0x5555;
	IWDG->PR = pr;
	IWDG->RLR = rlr;
	IWDG->KR = 0xAAAA;
	
	IWDG->KR = 0xCCCC;
}
