#include "pre.h"

void WWDG_Init(void)
{
	B1(RCC->APB1ENR,$RCC_WWDG_APB1);
	
	WWDG->CR = 0;
	WWDG->CR |= 0x7F;
	
	WWDG->CFR = 0;
	WWDG->CFR |= 3<<7;
	WWDG->CFR |= 0x5F;
	
	B1(WWDG->CR,7);
	
	B1(WWDG->CFR,9);
	B0(WWDG->SR,0);
	
	NVIC_SetPriority(WWDG_IRQn,NVIC_EncodePriority($NVIC_PriorityGroup,0,0));
	NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void)
{
	if(R1(WWDG->SR,0))
	{
		B0(WWDG->SR,0);
		//
	}
}
