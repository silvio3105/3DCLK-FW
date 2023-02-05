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
 * Configuration for HW_3DCLK_MAIN_rev1.
 * @{
 */

#define _3DCLK_HW_MAIN

// ----- HARDWARE MISC INFO
#define HW_VER						"22-0091rev1" /**< @brief Hardware version. 16 chars max! */


// ----- HARDWARE SELECTION
// MCUS
#define STM32L051K8 /**< @brief STM32L051K8 MCU. */

// LED CHIPS
#define IN_PI55TAT /**< @brief IN_PI55TAT RGB LED chip. */

// TEMPERATURE & HUMIDITY SENSORS
#define SHT40_AD /**< @brief SHT40_AD sensor. */
//#define SHT40_B /**< @brief SHT40_B sensor. */


// ----- MISC CONFIGURATION
#define DEVICE_CFGED_MARK			0xDEADBEEF /**< @brief Value in EEPROM that marks configured device. */
#define CLOCK_DEF_FORMAT			sRTC_time_format_t::FORMAT_24H /**< @brief Default time format. */
#define SYS_WAKEUP					10 /**< @brief System wakeup time in seconds. */
#define SYS_WAKEUP_CLOCK			sRTC_WUT_clock_t::CK_SPRE /**< @brief RTC wakeup clock for system wakeup. */
#define LEDS						9 /**< @brief Number of LEDs. */
#define LED_LINE					ProgLED_line_t::NON_BLOCKING /**< @brief LED line type. */
#define TNH_TEMP_UNIT				SHT40_unit_t::SHT40_UNIT_C /**< @brief Default temperature unit. */

// CONFIG IN DEBUG BUILD
#ifdef DEBUG
#define LOG_BUFF					128 /**< @brief Buffer size in bytes for logger. */
#endif // DEBUG


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
#define UART_BAUD					115200 /**< @brief Baud rate for UART for debugging. */
#define BLE_BAUD					9600 /**< @brief Baud rate for BLE module communication. */
#endif // STM32L051K8

// TEMPERATURE & HUMIDITY SENSOR
#ifdef SHT40_AD
#define TNH_SENS_ADDR				0x44 /**< @brief I2C address for SHT40-AD temperature sensor. */
#elif defined SHT40_AD
#define TNH_SENS_ADDR				0x45 /**< @brief I2C address for SHT40-B sensor. */
#endif

/** @} */

#endif // _HW_3DCLK_MAIN_rev1_H_

// END WITH NEW LINE
