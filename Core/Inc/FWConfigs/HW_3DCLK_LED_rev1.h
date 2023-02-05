/**
 * @file HW_3DCLK_LED_rev1.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief HW_3DCLK_LED_rev1 configuration.
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


#ifndef _HW_3DCLK_LED_rev1_H_
#define _HW_3DCLK_LED_rev1_H_


/** \defgroup HW_3DCLK_LED_rev1
 * Configuration for HW_3DCLK_LED_rev1 LED panel. LED segment and panel connections are described in "LED Segment & Panel.dwg" in project documentation.
 * @{
*/

#define _3DCLK_HW_LED 

// LEDs
#ifdef IN_PI55TAT
#define LED_FORMAT						ProgLED_format_t::PROG_LED_GRB /**< @brief LED format */
#define LED_BITS						24 /**< @brief LED width in bits. */
#define LED_L_VAL						3 /**< @brief Value representing bit 0. */
#define LED_H_VAL						5 /**< @brief Value representing bit 1. */
#endif // IN_PI55TAT

// LED SEGMENTS START INDEXES
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

/** @} */

#endif // _HW_3DCLK_LED_rev1_H_


// END WITH NEW LINE
