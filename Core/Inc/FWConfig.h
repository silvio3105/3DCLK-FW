/**
 * @file FWConfig.h
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


#ifndef _FWCONFIG_H_
#define _FWCONFIG_H_

/** \addtogroup FW_Config
 * 
 * Firmware configuration file.
 * @{
*/

// ----- FIRMWARE INFO "3DCLK v0.1rc1"
/**
 * @brief Firmware name.
 * 
 * Firmware name must not include ' '(space) character.
 * 
 * @warning 8 characters max!
 */
#define FW_NAME 			"3DCLK"

/**
 * @brief Firmware version.
 * 
 * Version format is: vM.mrXX or vM.mrcX
 * Examples: v1.5r15 v1.4rc8
 * 
 * @warning 7 characters max!
 */
#define FW_VER				"v1.0rc2"


// ----- HARDWARE SELECTION
// MAIN SELECTION
#define HW_3DCLK_MAIN_rev1 /**< @brief Macro for hardware selection. */

// LED SELECTION
#define HW_3DCLK_LED_rev1 /**< @brief Macro for LED hardware selection. */


// ----- MISC CONFIGURATION
// DEFAULT DEVICE CONFIGURATION
#define CFG_MARK					0xDEADBEEF /**< @brief Value in EEPROM that marks configured device. */
#define CFG_TIME_FORMAT				sRTC_time_format_t::FORMAT_24H /**< @brief Default time format. */

// SYSTEM STUFF
#define SYS_WAKEUP					1 /**< @brief System wakeup time in seconds. Used as "cycle tick". Watch for watchdog! */
#define SYS_WAKEUP_CLOCK			sRTC_WUT_clock_t::CK_SPRE /**< @brief RTC wakeup clock for system wakeup. */
#define SYS_WAKES_IN_MIN			(60 / SYS_WAKEUP) /**< @brief Number of wakeups in 60 seconds. Rounded to lower number(eg., 2.8 = 2). */

// INFO CYCLES
#define CYCLE_TICK_TIME				5 /**< @brief Number of cycle ticks which RTC time will be displayed. Duration of one cycle tick is defined with \ref SYS_WAKEUP */
#define CYCLE_TICK_DAY				3 /**< @brief Number of cycle ticks which RTC day will be displayed. Duration of one cycle tick is defined with \ref SYS_WAKEUP */
#define CYCLE_TICK_DATE				4 /**< @brief Number of cycle ticks which RTC date will be displayed. Duration of one cycle tick is defined with \ref SYS_WAKEUP */
#define CYCLE_TICK_TEMP				3 /**< @brief Number of cycle ticks which TnH temperature will be displayed. Duration of one cycle tick is defined with \ref SYS_WAKEUP */
#define CYCLE_TICK_RH				3 /**< @brief Number of cycle ticks which TnH humidity will be displayed. Duration of one cycle tick is defined with \ref SYS_WAKEUP */
#define CYCLE_TICK_SUM				(CYCLE_TICK_TIME + CYCLE_TICK_DAY + CYCLE_TICK_DATE + CYCLE_TICK_TEMP + CYCLE_TICK_RH) /**< @brief Sum of all cycle ticks. */

// LEDS
#ifdef DEBUG
#define LEDS						9 /**< @brief Number of LEDs. */
#else
#define LEDS						30 /**< @brief Number of LEDs. */
#endif // DEBUG
#define LED_LINE					ProgLED_line_t::NON_BLOCKING /**< @brief LED line type. */
#define LED_INFO_TOTAL				5 /**< @brief Total number of info can LED display will show. */
#define LED_BRIGHTNESS_UPDATE		1500 /**< @brief LED brightness update duration in ms. */
#define LED_UPDATE_THRESHOLD		3 /**< @brief Minimum difference in brightness for triggering LED brightness update. Keep below between 3-6%. */

// LED DEFAULT COLORS AND BRIGHTNESS
#define LED_MIN_BRIGHTNESS			1 /**< @brief Minimum LED line brightness. */
#define LED_MAX_BRIGHTNESS			100 /**< @brief Maximum LED line brightness. */

#define LED_COLOR_BLE_CONN			ProgLED_rgb_t::NEON_GREEN /**< @brief LED color if BLE has connection. */
#define LED_BRGHT_BLE_CONN			100 /**< @brief LED brightness if BLE has connection. */

#define LED_COLOR_ERROR				ProgLED_rgb_t::RED /**< @brief LED color for errors. */
#define LED_BRGHT_ERROR				8 /**< @brief LED brightness for errors. */

#define LED_COLOR_TIME				ProgLED_rgb_t::RED /**< @brief Default color for time info on LED display. */
#define LED_COLOR_DAY				ProgLED_rgb_t::YELLOW /**< @brief Default color for day info on LED display. */
#define LED_COLOR_DATE				ProgLED_rgb_t::ORANGE /**< @brief Default color for date info on LED display. */
#define LED_COLOR_TEMP				ProgLED_rgb_t::NEON_GREEN /**< @brief Default color for temperature info on LED display. */
#define LED_COLOR_RH				ProgLED_rgb_t::CYAN /**< @brief Default color for relative humidity info on LED display. */

// TNH STUFF
#define TNH_MEASURE_TYPE			SHT40_meas_t::TRH_H /**< @brief Default measure type for temperature and relative humidity. */
#define TNH_TICKS					10 /**< @brief Number of system ticks between two TnH measures. Period of one tick is defined with \ref SYS_WAKEUP  */

// BLE STUFF
#define BLE_RX_BUFFER				64 /**< @brief Size of buffer in bytes for BLE input. */

// CMD HANDLER STUFF
#define CMD_MAX_ARGS				10 /**< @brief Maximum number of argument that command handler can handle. */

// DEBUG STUFF
#ifdef DEBUG
#define LOG_METHOD					0 /**< @brief Logging method. \c 0 = \ref SYS_UART ; \c 1 = RTT on channel \ref LOG_RTT_CH */
#define LOG_BUFF					128 /**< @brief Buffer size in bytes for logger. */
#define LOG_RTT_CH					0 /**< @brief RTT channel. */
#define DEBUG_WAKEUP				/**< @brief Enable debug prints on RTC wakeup. */
//#define DEBUG_LED					/**< @brief Enable debug prints for LED display. */
//#define RTC_CLK_OUT				/**< @brief Simulate \c ck_spre clock output. Set to \c 1 to enable \c ck_spre clock output. */
#endif // DEBUG


// ----- HARDWARE CONFIGURATION
// HW_3DCLK_MAIN_rev1 hardware configuration
#ifdef HW_3DCLK_MAIN_rev1
#include "FWConfigs/HW_3DCLK_MAIN_rev1.h"
#endif // HW_3DCLK_MAIN_rev1

// HW_3DCLK_LED_rev1 configuration
#ifdef HW_3DCLK_LED_rev1
#include "FWConfigs/HW_3DCLK_LED_rev1.h"
#endif // HW_3DCLK_LED_rev1


// ----- CHECKS
#ifndef _3DCLK_HW_MAIN
#error "No main hardware configuration selected!"
#endif

#ifndef _3DCLK_HW_LED
#error "No LED hardware configuration selected!"
#endif

/**@ }*/

#endif // _FWCONFIG_H_

// END WITH NEW LINE
