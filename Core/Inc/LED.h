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
#include			"FWConfig.h"
#include			"ProgLED.h"

#include			<stdint.h>


// ----- ENUMS
/**
 * @brief LED panel indexes for \ref ledCharIdx array.
 * 
 */
enum led_panel_t : uint8_t {
	LED_PANEL1 = 1, /**< @brief Index for frist LED panel. */
	LED_PANEL2 = 2, /**< @brief Index for second LED panel. */
	LED_PANEL3 = 3, /**< @brief Index for third LED panel. */
	LED_PANEL4 = 4 /**< @brief Index for fourth LED panel. */
};


// ----- STRUCTS
/**
 * @brief Struct representing single 7-segment character.
 * 
 * @note Struct is aligned by 2 bytes.
 */
struct ledChar {
	const char ch = '\0'; /**< @brief 7-segment character. */
	const uint8_t bitmap = 0b00000000; /**< @brief Bitmap of \ref ch character(LSB->MSB). */
} __attribute__((packed, aligned(2)));

/**
 * @brief Struct for list of info to display.
 * 
 */
struct ledDisplayInfo {
	void (*infoHandler)(void); /**< @brief Pointer to info display function. */
	uint8_t durationTicks; /**< @brief Number of ticks info will be displayed. */
};


// ----- CLASSES
/**
 * @brief LED display class.
 * 
 * @tparam max Maximum number of info display can handle.
 */
template<uint8_t max>
class LedDisplay {
	// PUBLIC STUFF
	public:
	// CONSTRUCTOR & DECONSTRUCTOR DECLARATIONS
	LedDisplay(ledDisplayInfo* inputList)
	{
		list = inputList;
	}

	~LedDisplay(void)
	{
		list = nullptr;
	}

	// METHOD DECLARATIONS
	void tick(void)
	{
		// Increase tick counter
		tickCounter++;
		
		// If tick counter is greater than wanted
		if (tickCounter == list[currentInfo].durationTicks)
		{
			// Reset tick counter
			tickCounter = 0;

			// Move to next info
			currentInfo++;
			if (currentInfo == maxInfo) currentInfo = 0;
		}
		
		// Call display info handler
		list[currentInfo].infoHandler();
	}

	void reset(void)
	{
		// Reset tick counter and info index
		tickCounter = 0;
		currentInfo = 0;

		// Call display info handler
		list[currentInfo].infoHandler();
	}

	// PRIVATE STUFF
	private:
	// VARIABLES
	ledDisplayInfo* list = nullptr; /**< @brief Pointer to list of info to display. */
	uint8_t maxInfo = max; /**< @brief Length of \ref list */
	uint8_t currentInfo = 0; /**< @brief Index of current displayed info. */
	uint8_t tickCounter = 0; /**<@brief Tick counter. */
};


// ----- EXTERNS
extern ProgLED<LEDS, LED_FORMAT> LEDs;
extern LedDisplay<LED_INFO_TOTAL> Display;


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
 * @param str Pointer to string of maximum four characters.
 * @return No return value.
 * 
 * @warning Input string must be four characters long.
 * @warning No NULL character is needed.
 * @warning All characters must be written in upper-case.
 */
void ledPrint(const char* str);

/**
 * @brief Toggle semicolon LEDs.
 * 
 * @return No return value.
 */
void ledSmToggle(void);

/**
 * @brief Turn off semicolon LEDs.
 * 
 * @return No return value. 
 */
void ledSmOff(void);

/**
 * @brief Turn on semicolon LEDs.
 * 
 * @return No return value.
 */
void ledSmOn(void);

/**
 * @brief Update LED line.
 * 
 * @return No return value.
 */
void ledUpdate(void);

/**
 * @brief Show right aligned RST text.
 * 
 * @return No return value.
 */
void ledShowRST(void);

/**
 * @brief Show right aligned BLE text.
 * 
 * @return No return value.
 */
void ledShowBLE(void);

#endif // _LED_H_

// END WITH NEW LINE
