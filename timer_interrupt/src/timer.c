#include "timer.h"
#include "stm32f0xx_conf.h"


uint16_t PrescalerValue = 0;

void timer_init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* TIM16 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE);

    /* Enable the TIM16 gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* -----------------------------------------------------------------------
    TIM16 Configuration: Output Compare Timing Mode:

    In this example TIM16 input clock (TIM16CLK) is set to APB2 clock (PCLK2),
      => TIM16CLK = PCLK2 = SystemCoreClock = 48 MHz

    To get TIM16 counter clock at 60 KHz, the prescaler is computed as follows:
       Prescaler = (TIM16CLK / TIM16 counter clock) - 1
       Prescaler = (PCLK1 /6 MHz) - 1


    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.
  ----------------------------------------------------------------------- */

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) (SystemCoreClock  / 2000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 2000-1;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);


    /* Prescaler configuration */
    TIM_PrescalerConfig(TIM16, PrescalerValue, TIM_PSCReloadMode_Immediate);  // if want... currently this is not required.

    /* TIM Interrupts enable */
    TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);

    /* TIM16 enable counter */
    TIM_Cmd(TIM16, ENABLE);
}
