#include "main.h"
#include "uart.h"
#include <stdio.h>

//static void USART_SendString(USART_TypeDef* USARTx, char *Buffer);

void v_delay(uint32_t nCount)
{
    __IO uint32_t i;
    for(i=0; nCount > i; i++);
}

int main(void)
{
    v_uart_init();

    setbuf(stdout, NULL);
    printf("\r\nHello, Dongsik!\r\n");
    uint16_t cnt = 0;
    uint8_t* rx_val;
    while(1)
    {
        #if 0
        // USART_SendData(USART2, 0x39);
        // while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        // {}
        // USART_SendString(USART2, test_str);
        USART_SendString(USART2, "testing \r\n");
        #else
        //printf("cnt : %d \r\n", cnt++);
        #endif
        if ( uart_check_rx(rx_val))
        {
            printf("input : %c \r\n", *rx_val);
            printf("command : ");
            switch (*rx_val)
            {
                case '1':
                {
                    printf("control \r\n");
                    break;
                }
                case '2':
                {
                    printf("config \r\n");
                    break;
                }
                case '3':
                {
                    printf("init \r\n");
                    break;
                }
                case '4':
                {
                    printf("request \r\n");
                    break;
                }
                case '5':
                {
                    printf("feedback \r\n");
                    break;
                }
                default:
                {
                    printf("not registered \r\n");
                    break;
                }
            }
        }
    }
}

// static void USART_SendString(USART_TypeDef* USARTx, char *Buffer)
// {
//   while(*Buffer)
//   {
//     while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
//     USART_SendData(USARTx, *Buffer++);
//   }
// }

int _write(int file, char* p, int len)
{
    for (int i=0; i<len; i++)
    {
        USART_SendData(USART2, *(p+i));
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
    return len;
}
