/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_ll_adc.h"
#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_i2c.h"
#include "stm32l0xx_ll_iwdg.h"
#include "stm32l0xx_ll_crs.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_rtc.h"
#include "stm32l0xx_ll_tim.h"
#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include			"FWConfig.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/**
 * @brief Strust for build info.
 * 
 */
struct Build {
	char FW[16]; /**< @brief C-string for firmware version. */
	char HW[16]; /**< @brief C-string for hardware version. */
	char DATE[16]; /**< @brief C-string for build date. */
};

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern volatile uint32_t tick;
extern uint8_t initFlags;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/*#define LDR_Pin LL_GPIO_PIN_0
#define LDR_GPIO_Port GPIOA
#define TX_Pin LL_GPIO_PIN_2
#define TX_GPIO_Port GPIOA
#define RX_Pin LL_GPIO_PIN_3
#define RX_GPIO_Port GPIOA
#define DO_3V3_Pin LL_GPIO_PIN_5
#define DO_3V3_GPIO_Port GPIOA
#define BLE_SYS_Pin LL_GPIO_PIN_0
#define BLE_SYS_GPIO_Port GPIOB
#define BLE_LED_Pin LL_GPIO_PIN_1
#define BLE_LED_GPIO_Port GPIOB
#define BLE_LED_EXTI_IRQn EXTI0_1_IRQn
#define BLE_TX_Pin LL_GPIO_PIN_9
#define BLE_TX_GPIO_Port GPIOA
#define BLE_RX_Pin LL_GPIO_PIN_10
#define BLE_RX_GPIO_Port GPIOA
#define BLE_RST_Pin LL_GPIO_PIN_3
#define BLE_RST_GPIO_Port GPIOB*/
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

// SNIPPETS
#define delay					LL_mDelay /**< @brief Alias for LL_mDelay. */

// BITFIELDS
#define INIT_TNH_POS			0
#define INIT_TNH_MASK			0b00000001
#define INIT_TNH				(1 << INIT_TNH_POS)
#define INIT_LED_POS			1
#define INIT_LED_MASK			0b00000010
#define INIT_LED				(1 << INIT_LED_POS)
#define INIT_BLE_POS			2
#define INIT_BLE_MASK			0b00000100
#define INIT_BLE				(1 << INIT_BLE_POS)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
