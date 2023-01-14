/**
 * @file LED.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file for LED module.
 * @date 08.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _LED_H_
#define _LED_H_

// ----- INCLUDE FILES
#include			"config.h"
#include			"ProgLED.h"

#include			<stdint.h>


// ----- FUNCTION DECLARATIONS
/**
 * @brief LED line init.
 * 
 * @return No return value.
 */
void ledInit(void);


// ----- EXTERNS
extern ProgLED<LEDS, LED_FORMAT> LEDs;


#endif // _LED_H_

// END WITH NEW LINE
