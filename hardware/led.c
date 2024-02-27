#include "pre.h"

#define $LED6 3
#define $LED5 4
#define $LED4 5

void LED_Init(void)
{
	B1(RCC->AHB1ENR,1);
	
	B01(GPIOB->MODER,$LED6);
	B0(GPIOB->OTYPER,$LED6);
	B10(GPIOB->OSPEEDR,$LED6);
	B1(GPIOB->ODR,$LED6);
	
	B01(GPIOB->MODER,$LED5);
	B0(GPIOB->OTYPER,$LED5);
	B10(GPIOB->OSPEEDR,$LED5);
	B1(GPIOB->ODR,$LED5);
	
	B01(GPIOB->MODER,$LED4);
	B0(GPIOB->OTYPER,$LED4);
	B10(GPIOB->OSPEEDR,$LED4);
	B1(GPIOB->ODR,$LED4);
}

void LED_Set(u8 led,u8 state)
{
	u8 a=9-led;
	if(state)
		B0(GPIOB->ODR,a);
	else
		B1(GPIOB->ODR,a);
}

void LED_Reversal(u8 led)
{
	u8 a=9-led;
	if (R1(GPIOB->ODR,a))
		B0(GPIOB->ODR,a);
	else
		B1(GPIOB->ODR,a);
}
