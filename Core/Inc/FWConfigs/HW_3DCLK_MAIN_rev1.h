/**
 * @file HW_3DCLK_MAIN_rev1.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief HW_3DCLK_MAIN_rev1 configuration.
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


#ifndef _HW_3DCLK_MAIN_rev1_H_
#define _HW_3DCLK_MAIN_rev1_H_


/** \defgroup HW_3DCLK_MAIN_rev1
 * Configuration for HW_3DCLK_MAIN_rev1 hardware.
 * @{
 */


#define _3DCLK_HW_MAIN /**< @brief Main hardware configuration included. */


// ----- HARDWARE MISC INFO
#define HW_REV							"22-0091rev1" /**< @brief Hardware revision. 16 chars max! */


// ----- HARDWARE SELECTION
// MCUS
#ifndef STM32L051K8
#define STM32L051K8 /**< @brief STM32L051K8 MCU. */
#endif // STM32L051K8

// LED CHIPS
#define IN_PI55TAT /**< @brief IN_PI55TAT RGB LED chip. */

// TEMPERATURE & HUMIDITY SENSORS
#define SHT40_AD /**< @brief SHT40_AD sensor. */
//#define SHT40_B /**< @brief SHT40_B sensor. */


// ----- HARDWARE DEPENDED CONFIGURATION
// PINS
#ifdef STM32L051K8
#define LDR_Pin						LL_GPIO_PIN_0 /**< @brief GPIO pin for light depended resistor. */
#define LDR_GPIO_Port				GPIOA /**< @brief GPIO port for light depended resistor. */

#define TX_Pin						LL_GPIO_PIN_2 /**< @brief GPIO pin for UART2 TX. */
#define TX_GPIO_Port				GPIOA /**< @brief GPIO port for UART2 TX. */

#define RX_Pin						LL_GPIO_PIN_3 /**< @brief GPIO pin for UART2 RX. */
#define RX_GPIO_Port				GPIOA /**< @brief GPIO port for UART2 RX. */

#define DO_3V3_Pin					LL_GPIO_PIN_5 /**< @brief GPIO pin for LED data output. */
#define DO_3V3_GPIO_Port			GPIOA /**< @brief GPIO port for LED data output. */

#define BLE_SYS_Pin					LL_GPIO_PIN_0 /**< @brief GPIO pin for BLE system. */
#define BLE_SYS_GPIO_Port			GPIOB /**< @brief GPIO port for BLE system. */

#define BLE_LED_Pin					LL_GPIO_PIN_1 /**< @brief GPIO pin for BLE LED. */
#define BLE_LED_GPIO_Port			GPIOB /**< @brief GPIO port for BLE LED. */
#define BLE_LED_EXTI_IRQn			EXTI0_1_IRQn /**< @brief EXTI IRQ for BLE LED interrupt. */

#define BLE_TX_Pin					LL_GPIO_PIN_9 /**< @brief GPIO pin for BLE UART TX. */
#define BLE_TX_GPIO_Port			GPIOA /**< @brief GPIO port for BLE UART TX. */

#define BLE_RX_Pin					LL_GPIO_PIN_10 /**< @brief GPIO pin for BLE UART RX. */
#define BLE_RX_GPIO_Port			GPIOA /**< @brief GPIO port for BLE UART RX. */

#define BLE_RST_Pin					LL_GPIO_PIN_3 /**< @brief GPIO pin for BLE RST. */
#define BLE_RST_GPIO_Port			GPIOB /**< @brief GPIO port for BLE RST. */

#define RTC_CLK_GPIO_Pin			LL_GPIO_PIN_15 /**< @brief GPIO pin used for RTC clock output when enabled with \ref RTC_CLK_OUT */
#define RTC_CLK_GPIO_Port			GPIOA /**< @brief GPIO port used for RTC clock output when enabled with \ref RTC_CLK_OUT */
#endif // STM32L051K8

// WATCHDOG
#ifdef STM32L051K8
#define DOG_RELOAD					4095 /**< @brief Watchdog reload value. */
#define DOG_PRESCALER				iDog_prescaler_t::DIV256 /**< @brief Watchdog clock prescaler. */
#define DOG_MODE					iDog_mode_t::DBG_HALT /**< @brief Watchdog mode. */
#define DOG_HANDLE					IWDG /**< @brief Watchdog handle */
#endif // STM32L051K8

// EEPROM
#ifdef STM32L051K8
#define EEPROM_START				SEEPROM_START /**< @brief EEPROM start address in flash. */
#define EEPROM_LEN					SEEPROM_SIZE /**< @brief EEPROM sector size in bytes. */
#endif // STM32L051K8

// UARTS
#ifdef STM32L051K8
#define SYS_UART					USART2 /**< @brief UART for debugging. */
#define BLE_UART					USART1 /**< @brief UART for BLE module. */					
#define SYS_UART_BAUD				115200 /**< @brief Baud rate for debugging UART. */
#define BLE_UART_BAUD				9600 /**< @brief Baud rate for BLE module communication. */
#endif // STM32L051K8

// LED DATA
#ifdef STM32L051K8
#define LED_TIMER					TIM2 /**< @brief Timer PWM for LED data. */
#define LED_DMA						DMA1 /**< @brief DMA for \c LED_TIMER */
#define LED_DMA_CH					DMA1_Channel5 /**< @brief DMA channel for \ref LED_TIMER */
#endif // STM32L051K8

// LDR
#ifdef STM32L051K8
#define LDR_ADC						ADC1 /**< @brief ADC for measuring light with LDR. */

/**
 * @brief Minimum expected LDR value.
 * 
 * If measured LDR value is lower than this value, it will be set to value of \c LDR_MIN_VALUE macro.
 */
#define LDR_MIN_VALUE				60

/**
 * @brief Maximum expected LDR value.
 * 
 * If measured LDR value is greater than this value, it will be set to value of \c LDR_MAX_VALUE macro.
 */
#define LDR_MAX_VALUE				90
#endif // STM32L051K8

// LSE & RTC
#ifdef STM32L051K8
#define RTC_HANDLE					RTC /**< @brief Handle for RTC. */
#define RTC_CALIBRATE				/**< @brief Calibrate RTC with \ref RTC_CAL_DIR and \ref RTC_CAL_VALUE values. */
#define LSE_DRIVE					LL_RCC_LSEDRIVE_LOW /**< @brief LSE drive strength (RTC clock). */

/**
 * @brief Calibration direction.
 * 
 * When set to \c sRTC_cal_dir_t::RTC_CAL_POSITIVE RTC is calibrated with +488.5ppm.
 * 
 */
#define RTC_CAL_DIR					sRTC_cal_dir_t::RTC_CAL_NEGATIVE

/**
 * @brief Calibration value.
 * 
 * Calibration ppm is calculated using formula: \c (CALP*512-CALM)/(2^20-CALP*512+CALM)*10^6 where \c CALP is \c 0 or \c 1 and \c CALM is value between \c 0 and \c 511
 * \c CALP is selected with \ref RTC_CAL_DIR and \c CALM is selected with \ref RTC_CAL_VALUE macro.
 * Resolution of \c CALM is 0.954ppm. 
 * 
 */
#define RTC_CAL_VALUE				115
#define RTC_CAL_CYCLE				sRTC_cal_cycle_t::RTC_CAL_32S /**< @brief RTC calibration cycle period. */
#endif // STM32L051K8

// TEMPERATURE & HUMIDITY SENSOR
#ifdef SHT40_AD
#define TNH_SENS_ADDR				0x44 /**< @brief I2C address for SHT40-AD temperature sensor. */
#define TNH_TEMP_UNIT				SHT40_unit_t::SHT40_UNIT_C /**< @brief Default temperature unit. */
#elif defined SHT40_AD
#define TNH_SENS_ADDR				0x45 /**< @brief I2C address for SHT40-B sensor. */
#define TNH_TEMP_UNIT				SHT40_unit_t::SHT40_UNIT_C /**< @brief Default temperature unit. */
#endif

/** @} */

#endif // _HW_3DCLK_MAIN_rev1_H_

// END WITH NEW LINE
