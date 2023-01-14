/**
 * @file init.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file with CubeMX configuration.
 * @date 07.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _AAA_H
#define _AAA_H

// ----- INCLUDE FILES
#include			"config.h"


// ----- FUNCTION DECLARATIONS
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC_Init(void);
void MX_I2C1_Init(void);
void MX_RTC_Init(void);
void MX_TIM2_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
#ifndef DEBUG
void MX_IWDG_Init(void);
#endif // DEBUG

#endif // _INIT_H_

// END WITH NEW LINE
