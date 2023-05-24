#include "main.h"
#include "stm32f0xx_conf.h"
#include <stdio.h>

#define BOARD_LED_PORT           GPIOA
#define BOARD_LED_PIN            GPIO_Pin_5
#define BOARD_LED_GPIO_CLK       RCC_AHBPeriph_GPIOA

#define USART3_CLK          RCC_APB1Periph_USART3

#define USART3_TX_PIN       GPIO_Pin_10
#define USART3_TX_PORT      GPIOC
#define USART3_TX_CLK       RCC_AHBPeriph_GPIOC
#define USART3_TX_SOURCE    GPIO_PinSource10
#define USART3_TX_AF        GPIO_AF_1

#define USART3_RX_PIN       GPIO_Pin_11
#define USART3_RX_PORT      GPIOC
#define USART3_RX_CLK       RCC_AHBPeriph_GPIOC
#define USART3_RX_SOURCE    GPIO_PinSource11
#define USART3_RX_AF        GPIO_AF_1

#define DEBUG_USART     USART3

uint16_t arr[10] = {1,2,3,4,5,6,'a','b','c','d'};
char* str1 = "simdong";

static void led_init(void)
{
  GPIO_InitTypeDef    gpio_init_t;

  RCC_AHBPeriphClockCmd(BOARD_LED_GPIO_CLK, ENABLE);

  gpio_init_t.GPIO_Pin    = BOARD_LED_PIN;
  gpio_init_t.GPIO_Mode   = GPIO_Mode_OUT;
  gpio_init_t.GPIO_OType  = GPIO_OType_PP;
  gpio_init_t.GPIO_Speed  = GPIO_Speed_50MHz;
  gpio_init_t.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_Init(BOARD_LED_PORT, &gpio_init_t);
}

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

    USART_InitStructure.USART_BaudRate = 19200;
    // USART_InitStructure.USART_BaudRate = 1200;
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

int main(void)
{
    led_init();
    GPIO_WriteBit(BOARD_LED_PORT, BOARD_LED_PIN, 1);

    uart3_init();

    printf("sim dongsik \r\n");
    while(1)
    {
    }


    return 0;
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
