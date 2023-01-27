/**
 * @file config.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Firmware configuration file.
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


#ifndef _CONFIG_H_
#define _CONFIG_H_

/** \addtogroup FW_Config
 * 
 * Firmware configuration file.
 * @{
*/

// ----- VERSIONS
// SOFTWARE VERSION
#define FW_VER						"3DCLK v1.0rc1" /**< @brief Firmware version. 16 chars max! */

// HARDWARE MAIN REVISIONS
#define HW_3DCLK_MAIN_rev1			1 /**< @brief Hardware ID for rev1. */

// HARDWARE LED REVISIONS
#define HW_3DCLK_LED_rev1			1 /**< @brief Hardware ID for LED rev1. */

// MCUS
#define STM32L051K8					1 /**< @brief ID for STM32L051K8 MCU. */

// LED CHIPS
#define IN_PI55TAT					1 /**< @brief IN-PI55TAT LED chip. */

// TnH SENSORS
#define SHT40_AD					1 /**< @brief SHT40-AD temperature and humidity sensor. */
#define SHT40_B						2 /**< @brief SHT40-B temperature and humidity sensor. */


// ----- HARDWARE SELECTION
// MAIN SELECTION
#define HW_REV						HW_3DCLK_MAIN_rev1 /**< @brief Macro for hardware selection. */

// LED SELECTION
#define LED_REV						HW_3DCLK_LED_rev1 /**< @brief Macro for LED hardware selection. */


// ----- HARDWARE CONFIGURATION
// HW_3DCLK_MAIN_rev1 hardware configuration
#if (HW_REV == HW_3DCLK_MAIN_rev1)
#define HW_VER						"22-0091rev1" /**< @brief Hardware version. 16 chars max! */

#define MCU							STM32L051K8 /**< @brief MCU used by selected hardware version. */
#define LED_CHIP					IN_PI55TAT /**< @brief LED chip used by selected hardare version. */
#define TNH_SENSOR					SHT40_AD /**< @brief Temperature & humidity sensor used by selected hardware version. */
#endif // HW_REV

// HW_3DCLK_LED_rev1 LED configuration
#if (LED_REV == HW_3DCLK_LED_rev1)
#define LED_IDX_DOT						0 /**< @brief Index of first LED from semicolon. */
#define LED_IDX_1						2 /**< @brief Index of first LED from first LED PCB. */
#define LED_IDX_2						9 /**< @brief Index of first LED from second LED PCB. */
#define LED_IDX_3						16 /**< @brief Index of first LED from third LED PCB. */
#define LED_IDX_4						23 /**< @brief Index of first LED from fourth LED PCB. */

// LED SEGMENTS
#define LED_S1							(1 << 0) /**< @brief Macro for enabling LED segment 1. */
#define LED_S2							(1 << 1) /**< @brief Macro for enabling LED segment 2. */
#define LED_S3							(1 << 2) /**< @brief Macro for enabling LED segment 3. */
#define LED_S4							(1 << 3) /**< @brief Macro for enabling LED segment 4. */
#define LED_S5							(1 << 4) /**< @brief Macro for enabling LED segment 5. */
#define LED_S6							(1 << 5) /**< @brief Macro for enabling LED segment 6. */
#define LED_S7							(1 << 6) /**< @brief Macro for enabling LED segment 7. */
#endif // LED_REV


// ----- CONFIGURATION
// EEPROM
#if (MCU == STM32L051K8)
#define EEPROM_START					SEEPROM_START /**< @brief EEPROM start address in flash. */
#define EEPROM_LEN						SEEPROM_SIZE /**< @brief EEPROM sector size in bytes. */
#endif // MCU

// PINS
#if (HW_REV == HW_3DCLK_MAIN_rev1)
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
#endif // HW_REV

// WATCHDOG
#if (HW_REV == HW_3DCLK_MAIN_rev1)
#define DOG_RELOAD					4095 /**< @brief Watchdog reload value. */
#define DOG_PRESCALER				iDog_prescaler_t::DIV256 /**< @brief Watchdog clock prescaler. */
#define DOG_MODE					iDog_mode_t::DBG_HALT /**< @brief Watchdog mode. */
#define DOG_HANDLE					IWDG /**< @brief Watchdog handle */
#endif // HW_REV

// BUFFERS
#ifdef DEBUG
#define LOG_BUFF					128 /**< @brief Buffer size in bytes for logger. */
#endif // DEBUG

// UART
#if (HW_REV == HW_3DCLK_MAIN_rev1)
#define UART_BAUD					115200 /**< @brief Baud rate for UART for debugging. */
#define BLE_BAUD					115200 /**< @brief Baud rate for BLE module communication. */
#endif // HW_REV

// LEDs
#if (HW_REV == HW_3DCLK_MAIN_rev1)
#define LEDS						9 /**< @brief Number of LEDs. */
#define LED_LINE					ProgLED_line_t::NON_BLOCKING /**< @brief LED line type. */
#endif // HW_REV

#if (LED_CHIP == IN_PI55TAT)
#define LED_FORMAT					ProgLED_format_t::PROG_LED_GRB /**< @brief LED format */
#define LED_BITS					24 /**< @brief LED width in bits. */
#define LED_L_VAL					3 /**< @brief Value representing bit 0. */
#define LED_H_VAL					5 /**< @brief Value representing bit 1. */
#endif // LED_CHIP

// TEMPERATURE & HUMIDITY SENSOR
#if (HW_REV == HW_3DCLK_MAIN_rev1)
#define TNH_TEMP_UNIT				SHT40_unit_t::SHT40_UNIT_C /**< @brief Default temperature unit. */
#endif // HW_REV

#if (TNH_SENSOR == SHT40_AD)
#define TNH_SENS_ADDR				0x44 /**< @brief I2C address for SHT40-AD temperature sensor. */
#elif (TNH_SENSOR == SHT40_B)
#define TNH_SENS_ADDR				0x45 /**< @brief I2C address for SHT40-B sensor. */
#endif // TNH_SENSOR

// CLOCK
#define CLOCK_DEF_FORMAT			sRTC_time_format_t::FORMAT_24H /**< @brief Default time format. */


// ----- CHECKS
#if (HW_REV != HW_3DCLK_MAIN_rev1)
#error "Macro HW_REV not valid!"
#endif // HW_REV

/**@ }*/

#endif // _CONFIG_H_

// END WITH NEW LINE
