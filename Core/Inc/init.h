/**
 * @file init.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file with CubeMX configuration.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

/*
License

Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

Access and use of this Project and its contents are granted free of charge to any Person.
The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
Commercial use of this Project and its contents is prohibited.
Modifying this License and/or sublicensing is prohibited.

THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

This License shall be included in all methodal textual files.
*/


#ifndef _INIT_H
#define _INIT_H

// ----- INCLUDE FILES
#include			"FWConfig.h"


// ----- FUNCTION DECLARATIONS
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC_Init(void);
void MX_I2C1_Init(void);
void MX_TIM2_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

#endif // _INIT_H_

// END WITH NEW LINE
