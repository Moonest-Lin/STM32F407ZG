#include "stm32f4xx.h"

#define $NVIC_PriorityGroup 7-2

#define B0(data,x) data&=~(1<<x)
#define B1(data,x) data|=(1<<x)

#define B00(data,x) data&=~(3<<2*x)
#define B01(data,x) data=data&~(3<<2*x)|(1<<2*x)
#define B10(data,x) data=data&~(3<<2*x)|(2<<2*x)
#define B11(data,x) data|=(3<<2*x)

#define B0000(data,x) data&=~(15<<4*x)
#define B0001(data,x) data=data&~(15<<4*x)|(1<<4*x)
#define B0010(data,x) data=data&~(15<<4*x)|(2<<4*x)
#define B0011(data,x) data=data&~(15<<4*x)|(3<<4*x)
#define B0100(data,x) data=data&~(15<<4*x)|(4<<4*x)
#define B0101(data,x) data=data&~(15<<4*x)|(5<<4*x)
#define B0110(data,x) data=data&~(15<<4*x)|(6<<4*x)
#define B0111(data,x) data=data&~(15<<4*x)|(7<<4*x)
#define B1000(data,x) data=data&~(15<<4*x)|(8<<4*x)
#define B1001(data,x) data=data&~(15<<4*x)|(9<<4*x)
#define B1010(data,x) data=data&~(15<<4*x)|(10<<4*x)
#define B1011(data,x) data=data&~(15<<4*x)|(11<<4*x)
#define B1100(data,x) data=data&~(15<<4*x)|(12<<4*x)
#define B1101(data,x) data=data&~(15<<4*x)|(13<<4*x)
#define B1110(data,x) data=data&~(15<<4*x)|(14<<4*x)
#define B1111(data,x) data|=(7<<4*x)

#define R1(data,x) (data&1<<x)
#define R2(data,x) (data&3<<x)
#define R3(data,x) (data&7<<x)
#define R4(data,x) (data&15<<x)

#define $GPIOA_AHB1 0
#define $GPIOB_AHB1 1
#define $GPIOC_AHB1 2
#define $GPIOD_AHB1 3
#define $GPIOE_AHB1 4
#define $GPIOF_AHB1 5
#define $GPIOG_AHB1 6
#define $GPIOH_AHB1 7
#define $GPIOI_AHB1 8
#define $DMA1_AHB1 21
#define $DMA2_AHB1 22

#define $TIM2_APB1 0
#define $TIM3_APB1 1
#define $TIM4_APB1 2
#define $TIM5_APB1 3
#define $TIM6_APB1 4
#define $TIM7_APB1 5
#define $TIM12_APB1 6
#define $TIM13_APB1 7
#define $TIM14_APB1 8
#define $WWDG_APB1 11
#define $SPI2_APB1 14
#define $SPI3_APB1 15
#define $USART2_APB1 17
#define $USART3_APB1 18
#define $UART4_APB1 19
#define $UART5_APB1 20
#define $I2C1_APB1 21
#define $I2C2_APB1 22
#define $I2C3_APB1 23
#define $CAN1_APB1 25
#define $CAN2_APB1 26

#define $TIM1_APB2 0
#define $TIM8_APB2 1
#define $USART1_APB2 4
#define $USART6_APB2 5
#define $ADC1_APB2 8
#define $ADC2_APB2 9
#define $ADC3_APB2 10
#define $SDIO_APB2 11
#define $SPI1_APB2 12
#define $SYSCFGEN_APB2 14
#define $TIM9_APB2 16
#define $TIM10_APB2 17
#define $TIM11_APB2 18

#define $TIM_CEN_CR1 0
#define $TIM_UDIS_CR1 1
#define $TIM_URS_CR1 2
#define $TIM_OPM_CR1 3
#define $TIM_ARPE_CR1 7
#define $TIM_CKD0_CR1 8
#define $TIM_CKD1_CR1 9
