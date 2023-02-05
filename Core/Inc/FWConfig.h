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
#define FW_VER				"v0.1rc1"


// ----- HARDWARE SELECTION
// MAIN SELECTION
#define HW_3DCLK_MAIN_rev1 /**< @brief Macro for hardware selection. */

// LED SELECTION
#define HW_3DCLK_LED_rev1 /**< @brief Macro for LED hardware selection. */


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
