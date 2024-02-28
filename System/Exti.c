#include "pre.h"
#include "led.h"

#define $EXTI0 0

void EXTI0_Init(void)
{
	B1(RCC->AHB1ENR,$GPIOA_AHB1);
	B1(RCC->APB2ENR,$SYSCFGEN_APB2);
	
	B0000(SYSCFG->EXTICR[0],$EXTI0);
	
	B1(EXTI->RTSR,$EXTI0);
	B1(EXTI->FTSR,$EXTI0);
	
	NVIC_SetPriority(EXTI0_IRQn,NVIC_EncodePriority($NVIC_PriorityGroup,0,0));
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	B1(EXTI->PR,$EXTI0);
	
	B1(EXTI->IMR,$EXTI0);
}

u8 ExtiFlag=0;

void EXTI0_IRQHandler(void)
{
	if(R1(EXTI->PR,$EXTI0))
	{
		B1(EXTI->PR,$EXTI0);
		if(R1(GPIOA->IDR,$EXTI0))
		{
			B1(TIM6->CR1,0);
			ExtiFlag=0;
		}
		else if(!R1(GPIOA->IDR,$EXTI0))
		{
			B0(TIM6->CR1,0);
			ExtiFlag=1;
		}
	}
}
