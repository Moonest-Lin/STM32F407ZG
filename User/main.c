#include "stm32f4xx.h"
#include "led.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"
#include "RTC.h"
#include "pre.h"

int main(void)
{
	USART1_Init(115200);
	if(RTC_Init()==1)
	{
		printf("Success\r\n");
	}		
	else
	{
		printf("Fail\r\n");
	}	
	RTC_Alarm1ON();
	RTC_WUTON();
	while(1)
	{

	}
}

