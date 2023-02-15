/**
 * @file LED.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief LED module translation unit.
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


// ----- INCLUDE FILES
#include			"LED.h"
#include			"main.h"
#include			"FWConfig.h"
#include			"sStd.h"
#include			"ProgLED.h"

#include			"Log.h"
#include			"TnH.h"


// ----- FUNCTION DECLARATIONS
/**
 * @brief Handler for updating LED line.
 * 
 * @param bit Start bit when after clocking starts. \c -1 means to ignore parameter.
 * @return No return value.
 */
static void ledPWMStart(int8_t bit);

/**
 * @brief Handler for stopping LED line update.
 * 
 * @param bit Ignore this parameter.
 * @return No return value.
 */
static void ledPWMStop(int8_t bit);

/**
 * @brief Get character bitmap for LED 7-segment display.
 * 
 * @param c Character to search for bitmap.
 * @return Character bitmap. 
 */
static uint8_t getCharBitmap(const char c);

/**
 * @brief Display custom \c bitmap on \c panel 
 * 
 * @param panel LED panel where custom bitmap should be displayed. See \ref led_panel_t
 * @param bitmap Custom bitmap.
 * @return No return value.
 */
static void displayBitmap(const led_panel_t panel, const uint8_t bitmap);

static void ledDisplayTime(void);
static void ledDisplayDay(void);
static void ledDisplayDate(void);
static void ledDisplayTemp(void);
static void ledDsiplayRH(void);


// ----- VARIABLES
/**
 * @brief Character bitmap array.
 * 
 * LED segment and panel connections are described in "LED Segment & Panel.dwg" in project documentation.
 * 
 * @warning All letter are upper-case.
 */
const ledChar charBitmap[] = {
	// NUMBERS
	{ '0', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S7) },
	{ '1', (LED_S5 | LED_S7) },
	{ '2', (LED_S1 | LED_S2 | LED_S4 | LED_S5 | LED_S6) },
	{ '3', (LED_S1 | LED_S4 | LED_S5 | LED_S6 | LED_S7) },
	{ '4', (LED_S3 | LED_S5 | LED_S6 | LED_S7) },
	{ '5', (LED_S1 | LED_S3 | LED_S4 | LED_S6 | LED_S7) },
	{ '6', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S6 | LED_S7) },
	{ '7', (LED_S4 | LED_S5 | LED_S7) },
	{ '8', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S6 | LED_S7) },
	{ '9', (LED_S1 | LED_S3 | LED_S4 | LED_S5 | LED_S6 | LED_S7) },

	// LETTERS
	{ 'A', (LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S6 | LED_S7) },
	{ 'B', (LED_S1 | LED_S2 | LED_S3 | LED_S6 | LED_S7) },
	{ 'C', (LED_S1 | LED_S2 | LED_S3 | LED_S4) },
	{ 'D', (LED_S1 | LED_S2 | LED_S5 | LED_S6 | LED_S7) },
	{ 'E', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S6) },
	{ 'F', (LED_S2 | LED_S3 | LED_S4 | LED_S6) },
	{ 'H', (LED_S2 | LED_S3 | LED_S5 | LED_S6 | LED_S7) },
	{ 'I', (LED_S2 | LED_S3) },
	{ 'J', (LED_S1 | LED_S5 | LED_S7) },
	{ 'L', (LED_S1 | LED_S2 | LED_S3) },
	{ 'N', (LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S7) },
	{ 'O', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S7) },
	{ 'P', (LED_S2 | LED_S3 | LED_S4 | LED_S5 | LED_S6) },
	{ 'R', (LED_S2 | LED_S6) },
	{ 'S', (LED_S1 | LED_S3 | LED_S4 | LED_S6 | LED_S7) },
	{ 'U', (LED_S1 | LED_S2 | LED_S3 | LED_S5 | LED_S7) },
	{ 'Y', (LED_S1 | LED_S3 | LED_S5 | LED_S6 | LED_S7) },
	{ 'Z', (LED_S1 | LED_S2 | LED_S4 | LED_S5 | LED_S6) },
	{ 'T', (LED_S1 | LED_S2 | LED_S3 | LED_S6) },
	{ 'G', (LED_S1 | LED_S2 | LED_S3 | LED_S4 | LED_S7) },
	{ 'V', (LED_S2 | LED_S3 | LED_S5 | LED_S6) },

	// SYMBOLS
	{ ' ', 0 },
	{ '-', (LED_S6) },
	{ '_', (LED_S1) },
	{ '\\', (LED_S3 | LED_S6 | LED_S7) },
	{ '/', (LED_S2 | LED_S5 | LED_S6) }
};

/**
 * @brief Array with start start indexes for each LED PCB.
 * 
 * @warning Array order must be: Dot, LED1, LED2, LED3 & LED4!
 */
const uint8_t ledCharIdx[5] = {
	LED_IDX_DOT,
	LED_IDX_1,
	LED_IDX_2,
	LED_IDX_3,
	LED_IDX_4
};

ledDisplayInfo ledInfo[LED_INFO_MAX] = {
	{ ledDisplayTime, CYCLE_TICK_TIME },
	{ ledDisplayDay, CYCLE_TICK_DAY },
	{ ledDisplayDate, CYCLE_TICK_DATE },
	{ ledDisplayTemp, CYCLE_TICK_TEMP },
	{ ledDsiplayRH, CYCLE_TICK_RH }
};

uint8_t ledUpdateFlag = 0; /**< @brief LED update flag. If set, LEDs will be updated. */
display_info_t ledCurrentDisplay = display_info_t::DISPLAY_TIME; /**< @brief Current info displayed with LEDs. */


// ----- OBJECTS
/**
 * @brief LED line object.
 * 
 * \c LEDS number of LEDs.
 * \c LED_FORMAT LED color format.
 * \c ledPWMStart external function for updating LED line.
 * \c ledPWMStop external function for stopping LED line update.
 */
ProgLED<LEDS, LED_FORMAT> LEDs = ProgLED<LEDS, LED_FORMAT>(ledPWMStart, ledPWMStop);

LedDisplay<LED_INFO_MAX> Display = LedDisplay<LED_INFO_MAX>(ledInfo);


// ----- FUNCTION DEFINITIONS
static void ledPWMStart(int8_t bit)
{
	static uint8_t ledBits[LEDS * LED_BITS];

	log("LED DMA PWM Started\n");

	// Fill buffer for DMA
	LEDs.fillBuffer(ledBits, sizeof(ledBits), LEDS, LED_L_VAL, LED_H_VAL);

	// Disable DMA channel
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;

	// Clear DMA channel interrupt flags
	DMA1->IFCR = (DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTEIF5);

	// Set DMA channel data length
	DMA1_Channel5->CNDTR = 24 * LEDS;

	// Set DMA channel destination address
	DMA1_Channel5->CPAR = (uint32_t)(&(TIM2->CCR1));

	// Set DMA channel source address
	DMA1_Channel5->CMAR = (uint32_t)ledBits;

	// Disable Half transfer, transfer completed and transfer error interrupts
	DMA1_Channel5->CCR &= ~(DMA_CCR_HTIE | DMA_CCR_TCIE | DMA_CCR_TEIE);

	// Enable transfer completed interrupt
	DMA1_Channel5->CCR |= DMA_CCR_TCIE;

	// Enable DMA Channel
	DMA1_Channel5->CCR |=  DMA_CCR_EN;

	// TIM2 PWM
	// SOON: Add comments for lines below
	TIM2->CCER &= ~TIM_CCER_CC1E;
	TIM2->CCER |= TIM_CCER_CC1E;

	TIM2->DIER |= (TIM_DIER_CC1DE | TIM_DIER_UDE);

	TIM2->CR1 |= (TIM_CR1_URS | TIM_CR1_ARPE);

	// Enable TIM2
	TIM2->CR1 |= TIM_CR1_CEN;
}

static void ledPWMStop(int8_t bit)
{
	log("LED DMA PWM Stopped\n");
}

void ledInit(void)
{
	// Clear LED init flag
	SSTD_BIT_CLEAR(initFlags, INIT_LED_POS);

	// Init LED line and switch result
	switch (LEDs.init())
	{
		case PROG_LED_OK:
		{
			log("LEDs init OK\n");
			logf("Total LEDs %d\n", LEDS);

			// Set init flag for LED line
			SSTD_BIT_SET(initFlags, INIT_LED_POS);

			LEDs.rgb(ProgLED_rgb_t::RED);
			break;
		}

		case PROG_LED_NOK:
		{
			log("LEDs init NOT OK\n");
			break;
		}

		default:
		{
			log("LEDs init N/A\n");
			break;
		}
	}	
}

void ledUpdate(void)
{
	ledUpdateFlag = 0;
	LEDs.update(LED_LINE);
}

void ledPrint(const char* str)
{
	char bitmap = 0;

	// Loop through input four characters
	#ifdef DEBUG
	for (uint8_t i = 0; i < 1; i++)
	#else
	// Use all four LED panels
	for (uint8_t i = 0; i < 4; i++)
	#endif // DEBUG
	{
		// If NULL char is found, break
		if (!str[i]) break;

		// Get bitmap for character
		bitmap = getCharBitmap(str[i]);

		// Turn on or off LEDs using character bitmap
		for (uint8_t bIdx = 0; bIdx < 7; bIdx++)
		{
			if (SSTD_BIT(bitmap, bIdx)) LEDs.led[ledCharIdx[i + 1] + bIdx].on();
				else LEDs.led[ledCharIdx[i + 1] + bIdx].off();
		}
	}

	// Set LED update flag
	ledUpdateFlag = 1;	
}

void ledSmToggle(void)
{
	// Toggle semicolon LEDs
	LEDs.led[LED_IDX_DOT].toggle();
	LEDs.led[LED_IDX_DOT + 1].toggle();

	// Set LED update flag
	ledUpdateFlag = 1;
}

void ledSmOff(void)
{
	// Turn off semicolon LEDs
	LEDs.led[LED_IDX_DOT].off();
	LEDs.led[LED_IDX_DOT + 1].off();

	// Set LED update flag
	ledUpdateFlag = 1;	
}

void ledSmOn(void)
{
	// Turn on semicolon LEDs
	LEDs.led[LED_IDX_DOT].on();
	LEDs.led[LED_IDX_DOT + 1].on();

	// Set LED update flag
	ledUpdateFlag = 1;	
}

void ledPanelOff(const led_panel_t panel)
{
	// Turn off all LED segments for given LED panel
	for (uint8_t i = 0; i < 7; i++) LEDs.led[ledCharIdx[panel] + i].off();

	// Set LED update flag
	ledUpdateFlag = 1;
}

void displayPercent(void)
{
	// Display left part of percent sign
	uint8_t ledPercentBitmap = LED_S1 | LED_S2 | LED_S6 | LED_S7;
	displayBitmap(led_panel_t::LED_PANEL3, ledPercentBitmap);

	// Display right part of percent sign
	ledPercentBitmap = LED_S3 | LED_S4 | LED_S5 | LED_S6;
	displayBitmap(led_panel_t::LED_PANEL4, ledPercentBitmap);
}

// ----- STATIC FUNCTION DEFINITIONS
static uint8_t getCharBitmap(const char c)
{
	// Loop through character bitmap array
	for (uint8_t i = 0; i < SSTD_ARRAY(charBitmap); i++)
	{
		// If wanted character is found in bitmap array return its bitmap
		if (charBitmap[i].ch == c) return charBitmap[i].bitmap;
	}

	// If bitmap is not found, return _
	return LED_S1;
}

static void displayBitmap(const led_panel_t panel, const uint8_t bitmap)
{
	for (uint8_t i = 0; i < 7; i++)
	{
		// If bit i in bitmap is 1, turn on LED, otherwise turn off
		if (SSTD_BIT(bitmap, i)) LEDs.led[ledCharIdx[panel] + i].on();
			else LEDs.led[ledCharIdx[panel] + i].off();
	}

	// Set LED update flag
	ledUpdateFlag = 1;	
}

static void ledDisplayTime(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	LEDs.rgb(LED_COLOR_TIME);
	snprintf(str, sizeof(str), "%02d%02d", clockGetHour(), clockGetMinute());
	ledPrint(str);
	logf("Display[time] -> \"%s\"\n", str);
}

static void ledDisplayDay(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	LEDs.rgb(LED_COLOR_DAY);
	snprintf(str, sizeof(str), "DAY%d", clockGetWeekDay());
	ledPrint(str);
	logf("Display[day] -> \"%s\"\n", str);
}

static void ledDisplayDate(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	LEDs.rgb(LED_COLOR_DATE);
	snprintf(str, sizeof(str), "%02d%02d", clockGetDay(), clockGetMonth());
	ledPrint(str);
	logf("Display[date] -> \"%s\"\n", str);	
}

static void ledDisplayTemp(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	int8_t temp = 0;
	uint8_t ledPercentBitmap = LED_S3 | LED_S4 | LED_S5 | LED_S6;

	TnH.temperature(temp);
	temp = sStd::limit<int8_t>(temp, 0, 99);

	LEDs.rgb(LED_COLOR_TEMP);
	snprintf(str, sizeof(str), "%02d C", temp);
	ledPrint(str);
	displayBitmap(led_panel_t::LED_PANEL3, ledPercentBitmap);
	logf("Display[temp] -> \"%02d°C\"\n", temp);	
}

static void ledDsiplayRH(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	uint8_t rh = 0;

	TnH.rh(rh);
	if (rh > 99) rh = 99;

	LEDs.rgb(LED_COLOR_RH);
	snprintf(str, sizeof(str), "%02d", rh);
	ledPrint(str);
	displayPercent();
	logf("Display[rh] -> \"%02d%%\"\n", rh);		
}



// END WITH NEW LINE
