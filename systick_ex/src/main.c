#include "main.h"
#include <stdio.h>
#include "uart.h"

#define DEBUG_USART     USART3

static uint32_t cnt = 0;

int main(void)
{
    setbuf(stdout, NULL);
    uart_init();

    if (SysTick_Config(SystemCoreClock * 2))
    {
        /* Capture error */
        printf("error ??? \r\n");
        while (1);
    }
    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x0);

    printf("\r\nHello, Dongsik!\r\n");
    while(1)
    {
        uart_check_rx();
    }
}

int _write(int file, char* p, int len)
{
    for (int i=0; i<len; i++)
    {
        while(USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);
        USART_ClearFlag(DEBUG_USART, USART_ICR_TCCF);
        USART_SendData(DEBUG_USART, *(p+i));
    }
    while(USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TC) == RESET);

    return len;
}

void SysTick_Handler(void)
{
	printf("cnt : %ld s\r\n", ++cnt*2);
}