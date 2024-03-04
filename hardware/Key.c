#include "Key.h"

void KEY_Init(void)
{
	RCC->AHB1ENR |= 1<<0;
	
	GPIOA->MODER &= ~(3<<0*2);
	GPIOA->PUPDR &= ~(3<<0*2);
}

u8 KEY_Get(void)
{
	u8 Key_Num = 0;
	u8 Key_Flag = 0;
	if(GPIOA->IDR &= 1<<0)
	{
		Key_Flag = 1;
		Delay_ms(20);
		while(GPIOA->IDR &= 1<<0);
		Delay_ms(20);
		Key_Flag = 0;
		Key_Num = 1;
	}
	return Key_Num;
}
