/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_IT_H
#define __STM32F0XX_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI4_15_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
void SPL_GPIO_EXTI_Callback(uint32_t EXTI_Line);
#ifdef USE_STM32072B_EVAL
void EXTI2_3_IRQHandler(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_IT_H */

