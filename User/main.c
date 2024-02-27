#include "stm32f4xx.h"
#include "led.h"
#include "exti.h"
#include "usart.h"
#include "timer.h"
#include "stdio.h"

int main(void)
{
	u32 KeyTime;
	EXTI0_Init();
	USART_Init(115200);
	Timer6_Init();
	while(1)
	{
		if(ExtiFlag==1)
		{
			KeyTime=0;
			ExtiFlag=0;
			KeyTime=count*1000+TIM6->CNT*0.1;
			count=0;
			TIM6->CNT=0;
			printf("%d\r\n",KeyTime);
		}
	}
}

