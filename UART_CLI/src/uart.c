#include "uart.h"



uint8_t l_c_uart_rx_buf[16] = {0,};
static volatile uint32_t l_n_rx_idx = 0;
static volatile uint32_t l_n_read_idx = 0;

void v_comport_init(USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

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

    /* NVIC configuration */
    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

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

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void USART2_IRQHandler(void)
{
    if ( USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
        l_c_uart_rx_buf[l_n_rx_idx++ & 0x0F] = USART_ReceiveData(USART2);
    }
}

uint8_t uart_check_rx(uint8_t* i_p_value)
{
    if (l_n_rx_idx != l_n_read_idx)
    {
        // while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        // USART_SendData(USART2, l_c_uart_rx_buf[l_n_read_idx++ & 0x0F]);
        *i_p_value = l_c_uart_rx_buf[l_n_read_idx++ & 0x0F];
        return 1;
    }
    else
    {
        return 0;
    }
}
