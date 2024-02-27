#include "pre.h"

void Timer6_Init(void)
{
	B1(RCC->APB1ENR,4);
	
	B1(TIM6->CR1,7);
	B0(TIM6->CR1,3);
	
	B0(TIM6->CR1,2);
	B0(TIM6->CR1,1);
	
	TIM6->CNT = 0;
	TIM6->PSC = 8400-1;
	TIM6->ARR = 10000;
	
	B1(TIM6->EGR,0);
	B0(TIM6->SR,0);
	
	B1(TIM6->DIER,0);
	
	NVIC_SetPriority(TIM6_DAC_IRQn,NVIC_EncodePriority(7-2,0,0));
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	B0(TIM6->CR1,0);
}

u8 count=0;

void TIM6_DAC_IRQHandler(void)
{
	if(R1(TIM6->SR,0))
	{
		B0(TIM6->SR,0);
		count++;
	}
}
