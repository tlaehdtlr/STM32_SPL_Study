#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "timer.h"
#include "stm32f0xx_conf.h"


#define USER_LED_PORT           GPIOA
#define USER_LED_PIN            GPIO_Pin_5
#define USER_LED_GPIO_CLK       RCC_AHBPeriph_GPIOA

void led_on(void)
{
    USER_LED_PORT->BSRR = USER_LED_PIN;
}
void led_off(void)
{
    USER_LED_PORT->BRR = USER_LED_PIN;
}
void led_toggle(void)
{
    USER_LED_PORT->ODR ^= USER_LED_PIN;
}

void led_init(void)
{
    GPIO_InitTypeDef    gpio_init_t;

    RCC_AHBPeriphClockCmd(USER_LED_GPIO_CLK, ENABLE);

    gpio_init_t.GPIO_Pin    = USER_LED_PIN;
    gpio_init_t.GPIO_Mode   = GPIO_Mode_OUT;
    gpio_init_t.GPIO_OType  = GPIO_OType_PP;
    gpio_init_t.GPIO_Speed  = GPIO_Speed_50MHz;
    gpio_init_t.GPIO_PuPd   = GPIO_PuPd_NOPULL;
    GPIO_Init(USER_LED_PORT, &gpio_init_t);
}

uint32_t cnt1 = 0;
int main(void)
{
    led_init();
    timer_init();

    led_on();
    while(1)
    {
        if (cnt1++ == 10000000)
        {
            TIM_Cmd(TIM16, ENABLE);
            cnt1 = 0;
        }
    }
}

int cnt = 0;
void TIM16_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM16, TIM_IT_Update) != RESET)
    {
        switch (cnt++)
        {
            case 5:
            {
                TIM16->ARR = 1000-1;
            }
                break;
            case 10:
            {
                TIM16->ARR = 2000-1;
            }
                break;
            case 15:
            {
                TIM_Cmd(TIM16, DISABLE);
                cnt = 0;
            }
                break;
            default:
                break;
        }

        TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
        led_toggle();
    }
}
