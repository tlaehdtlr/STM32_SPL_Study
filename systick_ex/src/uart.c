#include "uart.h"
#include <stdio.h>

#define UART_RX_BUF_SIZE    256

static uint8_t              l_c_uart3_rx_buf[UART_RX_BUF_SIZE] = {0,};
static volatile uint32_t    l_n_uart3_rx_idx = 0;
static volatile uint32_t    l_n_uart3_read_idx = 0;


static void uart3_init(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(USART3_TX_CLK | USART3_RX_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(USART3_CLK, ENABLE);

    /* Connect PXx to USARTx_Tx */
    GPIO_PinAFConfig(USART3_TX_PORT, USART3_TX_SOURCE, USART3_TX_AF);

    /* Connect PXx to USARTx_Rx */
    GPIO_PinAFConfig(USART3_RX_PORT, USART3_RX_SOURCE, USART3_RX_AF);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = USART3_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(USART3_TX_PORT, &GPIO_InitStructure);

    /* Configure USART Rx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = USART3_RX_PIN;
    GPIO_Init(USART3_RX_PORT, &GPIO_InitStructure);


    /* NVIC configuration */
    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* USART configuration */
    USART_Init(USART3, &USART_InitStructure);
    /* Enable USART */
    USART_Cmd(USART3, ENABLE);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}


void uart_init(void)
{
    uart3_init();
}

void USART3_4_IRQHandler(void)
{
    if ( USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        l_c_uart3_rx_buf[l_n_uart3_rx_idx++ & (UART_RX_BUF_SIZE-1)] = USART_ReceiveData(USART3);
    }
}

void uart_check_rx(void)
{
    if (l_n_uart3_rx_idx != l_n_uart3_read_idx)
    {
        printf("input : %c \r\n", l_c_uart3_rx_buf[l_n_uart3_read_idx++ & (UART_RX_BUF_SIZE-1)]);
    }
}
