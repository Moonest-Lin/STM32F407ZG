#include "pre.h"

void LowPow_Init(void)
{
	B1(SCB->SCR,2);
	B1(RCC->APB1ENR,$RCC_PWR_APB1);
	
	B1(PWR->CR,1);
	B1(PWR->CR,2);
	
	B1(PWR->CSR,8);
	
	__WFI();
}
