#include "stm32f4xx.h"

#define $NVIC_PriorityGroup 7-2

#define B0(data,x) data&=~(1<<x)
#define B1(data,x) data|=(1<<x)

#define M2(x) x*2
#define M4(x) x*4

#define B00(data,x) data&=~(3<<x)
#define B01(data,x) data=data&~(3<<x)|(1<<x)
#define B10(data,x) data=data&~(3<<x)|(2<<x)
#define B11(data,x) data|=(3<<x)

#define B0000(data,x) data&=~(15<<4*x)
#define B0001(data,x) data=data&~(15<<x)|(1<<x)
#define B0010(data,x) data=data&~(15<<x)|(2<<x)
#define B0011(data,x) data=data&~(15<<x)|(3<<x)
#define B0100(data,x) data=data&~(15<<x)|(4<<x)
#define B0101(data,x) data=data&~(15<<x)|(5<<x)
#define B0110(data,x) data=data&~(15<<x)|(6<<x)
#define B0111(data,x) data=data&~(15<<x)|(7<<x)
#define B1000(data,x) data=data&~(15<<x)|(8<<x)
#define B1001(data,x) data=data&~(15<<x)|(9<<x)
#define B1010(data,x) data=data&~(15<<x)|(10<<x)
#define B1011(data,x) data=data&~(15<<x)|(11<<x)
#define B1100(data,x) data=data&~(15<<x)|(12<<x)
#define B1101(data,x) data=data&~(15<<x)|(13<<x)
#define B1110(data,x) data=data&~(15<<x)|(14<<x)
#define B1111(data,x) data|=(7<<4*x)

#define R1(data,x) (data&1<<x)
#define R2(data,x) (data&3<<x)
#define R3(data,x) (data&7<<x)
#define R4(data,x) (data&15<<x)

#define $RCC_GPIOA_AHB1 0
#define $RCC_GPIOB_AHB1 1
#define $RCC_GPIOC_AHB1 2
#define $RCC_GPIOD_AHB1 3
#define $RCC_GPIOE_AHB1 4
#define $RCC_GPIOF_AHB1 5
#define $RCC_GPIOG_AHB1 6
#define $RCC_GPIOH_AHB1 7
#define $RCC_GPIOI_AHB1 8
#define $RCC_DMA1_AHB1 21
#define $RCC_DMA2_AHB1 22

#define $RCC_TIM2_APB1 0
#define $RCC_TIM3_APB1 1
#define $RCC_TIM4_APB1 2
#define $RCC_TIM5_APB1 3
#define $RCC_TIM6_APB1 4
#define $RCC_TIM7_APB1 5
#define $RCC_TIM12_APB1 6
#define $RCC_TIM13_APB1 7
#define $RCC_TIM14_APB1 8
#define $RCC_WWDG_APB1 11
#define $RCC_SPI2_APB1 14
#define $RCC_SPI3_APB1 15
#define $RCC_USART2_APB1 17
#define $RCC_USART3_APB1 18
#define $RCC_UART4_APB1 19
#define $RCC_UART5_APB1 20
#define $RCC_I2C1_APB1 21
#define $RCC_I2C2_APB1 22
#define $RCC_I2C3_APB1 23
#define $RCC_CAN1_APB1 25
#define $RCC_CAN2_APB1 26
#define $RCC_PWR_APB1 28

#define $RCC_TIM1_APB2 0
#define $RCC_TIM8_APB2 1
#define $RCC_USART1_APB2 4
#define $RCC_USART6_APB2 5
#define $RCC_ADC1_APB2 8
#define $RCC_ADC2_APB2 9
#define $RCC_ADC3_APB2 10
#define $RCC_SDIO_APB2 11
#define $RCC_SPI1_APB2 12
#define $RCC_SYSCFGEN_APB2 14
#define $RCC_TIM9_APB2 16
#define $RCC_TIM10_APB2 17
#define $RCC_TIM11_APB2 18

#define $RCC_LSEON_BDCR 0
#define $RCC_LSERDY_BDCR 1
#define $RCC_RTCSEL_BDCR 8
#define $RCC_RTCEN_BDCR 15


#define $TIM_CEN_CR1 0
#define $TIM_UDIS_CR1 1
#define $TIM_URS_CR1 2
#define $TIM_OPM_CR1 3
#define $TIM_ARPE_CR1 7
#define $TIM_CKD0_CR1 8
#define $TIM_CKD1_CR1 9

#define $TIM_UIF_SR 0

#define $TIM_UG_EGR 0

#define $TIM_UIE_DIER 0


#define $USART_RE_CR1 2
#define $USART_TE_CR1 3
#define $USART_IDLEIE_CR1 4
#define $USART_RXNEIE_CR1 5
#define $USART_M_CR1 12
#define $USART_UE_CR1 13
#define $USART_OVER8_CR1 15

#define $USART_STOP_CR2 12


#define $RTC_ALRAWF_ISR 0
#define $RTC_ALRBWF_ISR 1
#define $RTC_WUTWF_ISR 2
#define $RTC_INITF_ISR 6
#define $RTC_INIT_ISR 7
#define $RTC_ALRAF_ISR 8
#define $RTC_WUTF_ISR 10

#define $RTC_FMT_CR 6
#define $RTC_ALRAE_CR 8
#define $RTC_ALRBE_CR 9
#define $RTC_WUTE_CR 10
#define $RTC_ALRAIE_CR 12
#define $RTC_WUTIE_CR 14

#define $RTC_MAK1_ALRMxR 7
#define $RTC_MAK2_ALRMxR 15
#define $RTC_MAK3_ALRMxR 23
#define $RTC_MAK4_ALRMxR 31


#define $PWR_DBP_CR 8
