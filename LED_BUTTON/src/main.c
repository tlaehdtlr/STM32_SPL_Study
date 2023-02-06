#include "main.h"

#define USER_LED_PORT       GPIOA
#define USER_LED_PIN        GPIO_Pin_5
#define USER_LED_GPIO_CLK   RCC_AHBPeriph_GPIOA

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
    //gpio_init_t.GPIO_PuPd   = GPIO_PuPd_DOWN;
    GPIO_Init(USER_LED_PORT, &gpio_init_t);
}

void v_user_led_on(void)
{
    USER_LED_PORT->BRR = USER_LED_PIN;
}

void v_user_led_off(void)
{
    USER_LED_PORT->BSRR = USER_LED_PIN;
}

int main(void)
{
    v_user_led_init();
    v_user_led_on();

    while(1)
    {
        v_user_led_on();
        v_delay(5000000);
        v_user_led_off();
        v_delay(5000000);
    }

    return 0;
}

