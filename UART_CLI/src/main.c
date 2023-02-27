#include "main.h"
#include "uart.h"
#include <stdio.h>
#include "board_config.h"

void v_delay(uint32_t nCount)
{
    __IO uint32_t i;
    for(i=0; nCount > i; i++);
}

int main(void)
{
    uart_init();

    setbuf(stdout, NULL);
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
