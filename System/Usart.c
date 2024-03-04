#include "pre.h"
#include "stdio.h"

void USART1_Init(u32 Bount)
{
	float UsartDiv;
	int zheng,xiao;
	
	B1(RCC->AHB1ENR,$RCC_GPIOA_AHB1);
	
	B10(GPIOA->MODER,M2(9));
	B0111(GPIOA->AFR[1],M4(1));
	
	B10(GPIOA->MODER,M2(10));
	B0111(GPIOA->AFR[1],M4(2));
	
	B1(RCC->APB2ENR,$RCC_USART1_APB2);
	
	B0(USART1->CR1,$USART_OVER8_CR1);
	B0(USART1->CR1,$USART_M_CR1);

	B0(USART1->CR2,$USART_STOP_CR2);
	
	UsartDiv = 84000000.0/(8*(2-0)*Bount);
	zheng = UsartDiv;
	xiao = (UsartDiv - zheng)*16;
	USART1->BRR = zheng<<4 | xiao;
	
	B1(USART1->CR1,$USART_RE_CR1);
	B1(USART1->CR1,$USART_TE_CR1);
	B1(USART1->CR1,$USART_UE_CR1);
}

//void USART3_Init(u32 Bount)
//{
//	float UsartDiv;
//	int zheng,xiao;
//	
//	B1(RCC->AHB1ENR,$RCC_GPIOB_AHB1);
//	
//	B10(GPIOB->MODER,10);
//	B1000(GPIOB->AFR[1],2);
//	
//	B10(GPIOB->MODER,11);
//	B1000(GPIOB->AFR[1],3);
//	
//	B1(RCC->APB1ENR,$RCC_USART3_APB1);
//	
//	B0(USART3->CR1,15);
//	B0(USART3->CR1,12);

//	B0(USART3->CR2,12);
//	
//	UsartDiv = 84000000.0/(8*(2-0)*Bount);
//	zheng = UsartDiv;
//	xiao = (UsartDiv - zheng)*16;
//	USART3->BRR = zheng<<4 | xiao;
//	
//	B1(USART3->CR1,3);
//	B1(USART3->CR1,2);
//	B1(USART3->CR1,13);
//}

int fputc(int data,FILE*file)
{
	while(!(USART1->SR &1<<7))
		{
		}
		USART1->DR = data;
		return data;
}

void USART1_Send(u8 *data)
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
