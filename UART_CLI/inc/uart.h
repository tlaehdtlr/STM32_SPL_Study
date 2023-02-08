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

void v_comport_init(USART_InitTypeDef* USART_InitStruct);
void v_uart_init(void);
uint8_t uart_check_rx(uint8_t* i_p_value);

#endif /* __UART_H */