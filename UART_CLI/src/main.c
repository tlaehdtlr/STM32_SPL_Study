#include "main.h"
#include <stdio.h>

#define USART2_CLK          RCC_APB1Periph_USART2

#define USART2_TX_PIN       GPIO_Pin_2
#define USART2_TX_PORT      GPIOA
#define USART2_TX_CLK       RCC_AHBPeriph_GPIOA
#define USART2_TX_SOURCE    GPIO_PinSource2
#define USART2_TX_AF        GPIO_AF_1

#define USART2_RX_PIN       GPIO_Pin_3
#define USART2_RX_PORT      GPIOA
#define USART2_RX_CLK       RCC_AHBPeriph_GPIOA
#define USART2_RX_SOURCE    GPIO_PinSource3
#define USART2_RX_AF        GPIO_AF_1

//static void USART_SendString(USART_TypeDef* USARTx, char *Buffer);

void v_comport_init(USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(USART2_TX_CLK | USART2_RX_CLK, ENABLE);

    /* Enable USART clock */
    RCC_APB1PeriphClockCmd(USART2_CLK, ENABLE);

    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(USART2_TX_PORT, USART2_TX_SOURCE, USART2_TX_AF);

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(USART2_RX_PORT, USART2_RX_SOURCE, USART2_RX_AF);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = USART2_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(USART2_TX_PORT, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = USART2_RX_PIN;
    GPIO_Init(USART2_RX_PORT, &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(USART2, USART_InitStruct);

    /* Enable USART */
    USART_Cmd(USART2, ENABLE);

}

void v_uart_init(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    v_comport_init(&USART_InitStructure);
}

void v_delay(uint32_t nCount)
{
    __IO uint32_t i;
    for(i=0; nCount > i; i++);
}

int main(void)
{
    v_uart_init();

    setbuf(stdout, NULL);
    // USART_SendString(USART2, "\r\n----------------Start----------------\r\n");
    printf("\r\nHello, Dongsik!\r\n");
    uint16_t cnt = 0;
    while(1)
    {
        #if 0
        // USART_SendData(USART2, 0x39);
        // while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        // {}
        // USART_SendString(USART2, test_str);
        USART_SendString(USART2, "testing \r\n");
        #else
        printf("cnt : %d \r\n", cnt++);
        #endif
        v_delay(5000000);
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
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        USART_SendData(USART2, *(p+i));
    }
    return len;
}
