#ifndef __BCD_H__
#define __BCD_H__

extern u8 hour,min,sec;
extern u8 year,mon,day,week;

u8 RTC_Init(void);
void Get_Time(u8 *hour,u8 *min,u8 *sec);
void Get_Date(u8 *year,u8 *mon,u8 *day,u8 *week);
void RTC_Alarm1ON(void);
void RTC_WUTON(void);

#endif

