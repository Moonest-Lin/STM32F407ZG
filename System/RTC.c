#include "pre.h"
#include "delay.h"
#include "stdio.h"
#include <string.h>

u8 hour,min,sec;
u8 year,mon,day,week;
char *_time = __TIME__;//"15:51:29"
char *_date = __DATE__;//"Mar  1 2024"
char *month[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char _mon[4];

u32 DECtoBCD(u32 num)
{
    u32 label=10,i=16,bcd=0;
	while(num>=label)
    {
        label *= 10;
        i *= 16;
    }
	label /= 10;
    i /= 16;
	while(label>0)
	{
		bcd += num/label%10*i;
		label /= 10;
        i /= 16;
	}
	return bcd;
}

u32 BCDtoDEC(u32 num)
{
    u32 label=16,i=10,dec=0;
	while(num>=label)
    {
        label *= 16;
        i *= 10;
    }
	label /= 16;
    i /= 10;
	while(label>0)
	{
		dec += num/label%16*i;
		label /= 16;
        i /= 10;
	}
	return dec;
}

void Set_Time(u8 hour,u8 min,u8 sec)
{
	RTC->TR = DECtoBCD(hour)<<16 | DECtoBCD(min)<<8 | DECtoBCD(sec)<<0;
}

void Set_Date(u8 year,u8 mon,u8 day,u8 week)
{
	RTC->DR = DECtoBCD(year)<<16 | DECtoBCD(mon)<<8 | DECtoBCD(day)<<0 | DECtoBCD(week)<<13;
}

void Get_Time(u8 *hour,u8 *min,u8 *sec)
{
	u32 temp = RTC->TR;
	*hour = BCDtoDEC((temp >>16)&0x3f);
	*min = BCDtoDEC((temp >>8)&0x7f);
	*sec = BCDtoDEC(temp&0x7f);
}

void Get_Date(u8 *year,u8 *mon,u8 *day,u8 *week)
{
	u32 temp = RTC->DR;
	*year = BCDtoDEC((temp >>16)&0xff);
	*mon = BCDtoDEC((temp >>8)&0x1f);
	*day = BCDtoDEC(temp&0x3f);
	*week = (temp >> 13)& 0x07;
}

u8 RTC_Init(void)
{
	u16 temp = 0;
	if(RTC->BKP0R != 0x66)
	{
		B1(RCC->APB1ENR,$RCC_PWR_APB1);
		B1(PWR->CR,$PWR_DBP_CR);
		B1(RCC->BDCR,$RCC_RTCSEL_BDCR);
		B1(RCC->BDCR,$RCC_LSEON_BDCR);
		while(!R1(RCC->BDCR,$RCC_LSERDY_BDCR))
		{
			temp++;
			Delay_ms(1);
			if(temp>5000)
				return 2;
		}
		B1(RCC->BDCR,$RCC_RTCEN_BDCR);
		
		RTC->WPR = 0xCA;
		RTC->WPR = 0x53;
		
		B1(RTC->ISR,$RTC_INIT_ISR);
		temp = 0;
		while(!R1(RTC->ISR,$RTC_INITF_ISR))
		{
			temp++;
			Delay_ms(1);
			if(temp>5000)
				return 2;
		}
		
		RTC->PRER |= 256-1;
		RTC->PRER |= (128-1)<<16;
		B0(RTC->CR,$RTC_FMT_CR);
		
		hour = (_time[0] - '0')*10 + _time[1] - '0';
		min = (_time[3] - '0')*10 + _time[4] - '0';
		sec = (_time[6] - '0')*10 + _time[7] - '0';
		year = (_date[9] - '0')*10 + _date[10] - '0';
		_mon[0]=_date[0];
		_mon[1]=_date[1];
		_mon[2]=_date[2];
		_mon[3]=0;
		for(u8 i=0;i<12;i++)
		{
			if(!strcmp(_mon,month[i]))
				mon = i+1;
		}
		if(_date[4]!=' ')
		{
			day = (_date[4] - '0')*10 + _date[5] - '0';
		}
		else
		{
			day = _date[5] - '0';
		}
		printf("%d-%d-%d  %d:%d:%d\r\n",year,mon,day,hour,min,sec);
		Set_Time(hour,min,sec);
		Set_Date(year,mon,day,week);

		B0(RTC->ISR,$RTC_INIT_ISR);
		
		RTC->BKP0R = 0x666;
		RTC->WPR = 0x33;
		return 1;
	}
	else
	{
		Get_Time(&hour,&min,&sec);
		Get_Date(&year,&mon,&day,&week);
		return 0;
	}
}

void RTC_Alarm1ON(void)
{
	u16 temp;
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
	
	B1(RTC->ISR,$RTC_INIT_ISR);
	temp = 0;
	while(!R1(RTC->ISR,$RTC_INITF_ISR))
	{
		temp++;
		Delay_ms(1);
		if(temp>5000)
			return;
	}
	
	B0(RTC->CR,$RTC_ALRAE_CR);
	temp = 0;
	while(!R1(RTC->ISR,$RTC_ALRAWF_ISR))
	{
		temp++;
		Delay_ms(1);
		if(temp>5000)
			return;
	}
	
	B1(RTC->ALRMAR,$RTC_MAK4_ALRMxR);
	B1(RTC->ALRMAR,$RTC_MAK3_ALRMxR);
	B1(RTC->ALRMAR,$RTC_MAK2_ALRMxR);
	B0(RTC->ALRMAR,$RTC_MAK1_ALRMxR);
	
	B0101(RTC->ALRMAR,0);
	
	B1(EXTI->IMR,17);
	
	B1(EXTI->RTSR,17);
	
	B1(RTC->CR,$RTC_ALRAIE_CR);
	
	NVIC_SetPriority(RTC_Alarm_IRQn,NVIC_EncodePriority($NVIC_PriorityGroup,0,0));
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	
	B1(EXTI->PR,17);
	
	B1(RTC->CR,$RTC_ALRAE_CR);
	B0(RTC->ISR,$RTC_INIT_ISR);

	RTC->WPR = 0x33;
}

void RTC_WUTON(void)
{
	u16 temp;
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;
	
	B1(RTC->ISR,$RTC_INIT_ISR);
	temp = 0;
	while(!R1(RTC->ISR,$RTC_INITF_ISR))
	{
		temp++;
		Delay_ms(1);
		if(temp>5000)
			return;
	}
	
	B0(RTC->CR,$RTC_WUTE_CR);
	temp = 0;
	while(!R1(RTC->ISR,$RTC_WUTWF_ISR))
	{
		temp++;
		Delay_ms(1);
		if(temp>5000)
			return;
	}
	B10(RTC->CR,1);
	RTC->WUTR=0;
	
	B1(EXTI->IMR,22);
	
	B1(EXTI->RTSR,22);
	
	B1(RTC->CR,$RTC_WUTIE_CR);
	
	NVIC_SetPriority(RTC_WKUP_IRQn,NVIC_EncodePriority($NVIC_PriorityGroup,1,0));
	NVIC_EnableIRQ(RTC_WKUP_IRQn);
	
	B1(EXTI->PR,22);
	B0(RTC->ISR,$RTC_WUTF_ISR);
	
	B1(RTC->CR,$RTC_WUTE_CR);
	B0(RTC->ISR,$RTC_INIT_ISR);

	RTC->WPR = 0x33;
}

void RTC_Alarm_IRQHandler(void)
{
	if(R1(EXTI->PR,17))
	{
		B1(EXTI->PR,17);
		B0(RTC->ISR,$RTC_ALRAF_ISR);
		B0(RTC->ISR,$RTC_WUTF_ISR);
		printf("Alarm_IRQHandler\r\n");
	}
}

void RTC_WKUP_IRQHandler(void)
{
	if(R1(EXTI->PR,22))
	{
		B1(EXTI->PR,22);
		B0(RTC->ISR,$RTC_WUTF_ISR);
		Get_Time(&hour,&min,&sec);
		Get_Date(&year,&mon,&day,&week);
		printf("20%d-%02d-%02d  %02d:%02d:%02d\r\n",year,mon,day,hour,min,sec);
	}
}
