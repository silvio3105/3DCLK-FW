/**
 * @file LED.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file for LED module.
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


#ifndef _LED_H_
#define _LED_H_

// ----- INCLUDE FILES
#include			"config.h"
#include			"ProgLED.h"

#include			<stdint.h>


// ----- DEFINES
/**
 * @brief Snippet for calling LED line update.
 * 
 */
#define LED_UPDATE \
	LEDs.update(LED_LINE)


// ----- STRUCTS
/**
 * @brief Struct representing single 7-segment character.
 * 
 * @note Struct is aligned by 2 bytes.
 */
struct ledChar
{
	const char ch = '\0'; /**< @brief 7-segment character. */
	const uint8_t bitmap = 0b00000000; /**< @brief Bitmap of \ref ch character(LSB->MSB). */
} __attribute__((packed, aligned(2)));


// ----- FUNCTION DECLARATIONS
/**
 * @brief LED line init.
 * 
 * @return No return value.
 */
void ledInit(void);

/**
 * @brief Print four characters to 7-segment display.
 * 
 * @param c Pointer to string of four characters.
 * @return No return value.
 * 
 * @warning Input string must be four characters long.
 * @warning No NULL character is needed.
 * @warning All characters must be written in upper-case.
 */
void ledPrint(const char* c);

/**
 * @brief Toggle semicolon LEDs.
 * 
 * @return No return value.
 */
void toggleSemicolon(void);


// ----- EXTERNS
extern ProgLED<LEDS, LED_FORMAT> LEDs;
extern const ledChar charBitmap[]; // SOON: Test


#endif // _LED_H_

// END WITH NEW LINE
