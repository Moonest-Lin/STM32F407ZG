#include "pre.h"

void Timer6_Init(void)
{
	B1(RCC->APB1ENR,$RCC_TIM6_APB1);
	
	B1(TIM6->CR1,$TIM_ARPE_CR1);
	B0(TIM6->CR1,$TIM_OPM_CR1);
	
	B0(TIM6->CR1,$TIM_URS_CR1);
	B0(TIM6->CR1,$TIM_UDIS_CR1);
	
	TIM6->CNT = 0;
	TIM6->PSC = 8400-1;
	TIM6->ARR = 10000;
	
	B1(TIM6->EGR,$TIM_UG_EGR);
	B0(TIM6->SR,$TIM_UIF_SR);
	
//	B1(TIM6->DIER,$TIM_UIE_DIER);
//	
//	NVIC_SetPriority(TIM6_DAC_IRQn,NVIC_EncodePriority($NVIC_PriorityGroup,0,0));
//	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	B0(TIM6->CR1,$TIM_CEN_CR1);
}

u8 count=0;

void TIM6_DAC_IRQHandler(void)
{
	if(R1(TIM6->SR,$TIM_UIF_SR))
	{
		B0(TIM6->SR,$TIM_UIF_SR);
		count++;
	}
}
