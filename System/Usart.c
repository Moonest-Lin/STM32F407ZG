#include "pre.h"
#include "stdio.h"

void USART_Init(u32 Bount)
{
	float UsartDiv;
	int zheng,xiao;
	
	B1(RCC->AHB1ENR,0);
	
	B10(GPIOA->MODER,9);
	B0111(GPIOA->AFR[1],1);
	
	B10(GPIOA->MODER,10);
	B0111(GPIOA->AFR[1],2);
	
	B1(RCC->APB2ENR,4);
	
	B0(USART1->CR1,15);
	B0(USART1->CR1,12);

	B0(USART1->CR2,12);
	
	UsartDiv = 84000000.0/(8*(2-0)*Bount);
	zheng = UsartDiv;
	xiao = (UsartDiv - zheng)*16;
	USART1->BRR = zheng<<4 | xiao;
	
	B1(USART1->CR1,3);
	B1(USART1->CR1,2);
	B1(USART1->CR1,13);
}

int fputc(int data,FILE*file)
{
	while(!(USART1->SR &1<<7))
		{
		}
		USART1->DR = data;
		return data;
}

void USART_Send(u8 *data)
{
	while(*data != 0)
	{
		while(!(USART1->SR &1<<7))
		{
		}
		USART1->DR = *data;
		data++;
	}
}
