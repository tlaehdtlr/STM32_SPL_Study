#ifndef __UART_H
#define __UART_H

#include "stm32f0xx_conf.h"

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


/*

*/
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


///////////
#define USART6_CLK          RCC_APB2Periph_USART6

#define USART6_TX_PIN       GPIO_Pin_4
#define USART6_TX_PORT      GPIOA
#define USART6_TX_CLK       RCC_AHBPeriph_GPIOA
#define USART6_TX_SOURCE    GPIO_PinSource4
#define USART6_TX_AF        GPIO_AF_5

#define USART6_RX_PIN       GPIO_Pin_5
#define USART6_RX_PORT      GPIOA
#define USART6_RX_CLK       RCC_AHBPeriph_GPIOA
#define USART6_RX_SOURCE    GPIO_PinSource5
#define USART6_RX_AF        GPIO_AF_5

#define USART6_DE_PIN       GPIO_Pin_7
#define USART6_DE_PORT      GPIOD
#define USART6_DE_CLK       RCC_AHBPeriph_GPIOD

void uart_init(void);
void uart_check_rx(void);

#endif /* __UART_H */
