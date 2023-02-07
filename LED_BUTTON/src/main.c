#include "main.h"
#include <stdbool.h>

#define USER_LED_PORT           GPIOA
#define USER_LED_PIN            GPIO_Pin_5
#define USER_LED_GPIO_CLK       RCC_AHBPeriph_GPIOA

#define USER_BUTTON_PORT        GPIOC
#define USER_BUTTON_PIN         GPIO_Pin_13
#define USER_BUTTON_GPIO_CLK    RCC_AHBPeriph_GPIOC

static bool l_b_led_toggle = false;

void v_delay(uint32_t nCount)
{
    __IO uint32_t i;
    for(i=0; nCount > i; i++);
}

void v_user_led_init(void)
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

void v_user_led_on(void)
{
    USER_LED_PORT->BSRR = USER_LED_PIN;
}

void v_user_led_off(void)
{
    USER_LED_PORT->BRR = USER_LED_PIN;
}

void v_user_led_toggle_start(void)
{
    v_user_led_on();
    v_delay(5000000);
    v_user_led_off();
    v_delay(5000000);
}

void v_button_init(void)
{
    GPIO_InitTypeDef    gpio_init_t;
    EXTI_InitTypeDef    exti_init_t;
    NVIC_InitTypeDef    nvic_init_t;

    RCC_AHBPeriphClockCmd(USER_BUTTON_GPIO_CLK, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    gpio_init_t.GPIO_Pin    = USER_BUTTON_PIN;
    gpio_init_t.GPIO_Mode   = GPIO_Mode_IN;
    gpio_init_t.GPIO_OType  = GPIO_OType_PP;
    gpio_init_t.GPIO_Speed  = GPIO_Speed_50MHz;
    gpio_init_t.GPIO_PuPd   = GPIO_PuPd_NOPULL;
    GPIO_Init(USER_BUTTON_PORT, &gpio_init_t);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

    exti_init_t.EXTI_Line = EXTI_Line13;
    exti_init_t.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init_t.EXTI_Trigger = EXTI_Trigger_Falling;
    exti_init_t.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_init_t);

    /* Enable and set EXTI4_15 Interrupt */
    nvic_init_t.NVIC_IRQChannel = EXTI4_15_IRQn;
    nvic_init_t.NVIC_IRQChannelPriority = 0x00;
    nvic_init_t.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_t);
}

void SPL_GPIO_EXTI_Callback(uint32_t EXTI_Line)
{
    if ( EXTI_Line == EXTI_Line13)
    {
        if ( l_b_led_toggle)
        {
            l_b_led_toggle = false;
        }
        else
        {
            l_b_led_toggle = true;
        }
    }
}

int main(void)
{
    v_user_led_init();
    v_user_led_on();
    v_button_init();

    while(1)
    {
        if ( l_b_led_toggle)
        {
            v_user_led_toggle_start();
        }
        else
        {
            v_user_led_on();
        }
    }

    return 0;
}

