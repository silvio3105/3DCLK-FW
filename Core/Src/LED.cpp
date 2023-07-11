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
#include			"LDR.h"


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
 * @warning All letter must be upper-case.
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

ledDisplayInfo ledInfo[LED_INFO_TOTAL] = {
	{ ledDisplayTime, CYCLE_TICK_TIME },
	{ ledDisplayDay, CYCLE_TICK_DAY },
	{ ledDisplayDate, CYCLE_TICK_DATE },
	{ ledDisplayTemp, CYCLE_TICK_TEMP },
	{ ledDsiplayRH, CYCLE_TICK_RH }
};

uint8_t ledUpdateFlag = 0; /**< @brief LED update flag. If set, LEDs will be updated. */
uint8_t ledCurrentBrightness = 10; /**< @brief Current LED line brightness. */
uint8_t ledTargetBrightness = 0; /**< @brief Target LED line brightness. */
led_update_brightness_dir_t ledBrightnessUpdateDir = led_update_brightness_dir_t::LED_UPDATE_POS; /**< @brief LED line brightness update direction indicator. */
uint16_t ledBrightnessUpdatePeriod = 0; /**< @brief LED brightness update period in ms. */
uint32_t ledLastUpdateTick = 0; /**< @brief Tick of last LED brightness update. */


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

/**
 * @brief LED display object.
 * 
 * \c LED_INFO_TOTAL Number of info display will cycle.
 * \c ledInfo Pointer to list of info display will cycle.
 */
LedDisplay<LED_INFO_TOTAL> Display = LedDisplay<LED_INFO_TOTAL>(ledInfo);


// ----- FUNCTION DEFINITIONS
static void ledPWMStart(int8_t bit)
{
	static uint8_t ledBits[LEDS * LED_BITS];

	#ifdef DEBUG_LED
	log("LED DMA PWM Started\n");
	#endif // DEBUG_LED

	// Fill buffer for DMA
	LEDs.fillBuffer(ledBits, sizeof(ledBits), LEDS, LED_L_VAL, LED_H_VAL);

	// Disable DMA channel
	LED_DMA_CH->CCR &= ~DMA_CCR_EN;

	// Clear DMA channel interrupt flags
	LED_DMA->IFCR = (DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5 | DMA_IFCR_CTEIF5);

	// Set DMA channel data length
	LED_DMA_CH->CNDTR = 24 * LEDS;

	// Set DMA channel destination address
	LED_DMA_CH->CPAR = (uint32_t)(&(LED_TIMER->CCR1));

	// Set DMA channel source address
	LED_DMA_CH->CMAR = (uint32_t)ledBits;

	// Disable Half transfer, transfer completed and transfer error interrupts
	LED_DMA_CH->CCR &= ~(DMA_CCR_HTIE | DMA_CCR_TCIE | DMA_CCR_TEIE);

	// Enable transfer completed interrupt
	LED_DMA_CH->CCR |= DMA_CCR_TCIE;

	// Enable DMA Channel
	LED_DMA_CH->CCR |=  DMA_CCR_EN;

	// PWM
	// Enable capture/compare channel 1
	LED_TIMER->CCER &= ~TIM_CCER_CC1E;
	LED_TIMER->CCER |= TIM_CCER_CC1E;

	// Enable DMA for CC channel 1
	LED_TIMER->DIER |= (TIM_DIER_CC1DE | TIM_DIER_UDE);

	// Enable auto reload and update for CC1
	LED_TIMER->CR1 |= (TIM_CR1_URS | TIM_CR1_ARPE);

	// Enable TIM2
	LED_TIMER->CR1 |= TIM_CR1_CEN;
}

static void ledPWMStop(int8_t bit)
{
	#ifdef DEBUG_LED
	log("LED DMA PWM Stopped\n");
	#endif // DEBUG_LED
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
	// Abort if update is not needed
	if (!ledUpdateFlag) return;

	// Reset update flag
	ledUpdateFlag = 0;

	// Update LED display
	LEDs.update(LED_LINE);
}

void ledPrint(const char* str)
{
	char bitmap = 0;

	// Loop through input four characters
	#ifdef DEBUG
	// Use only first LED panel
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

void ledShowRST(void)
{
	// Set ERROR color and brightness
	LEDs.rgb(LED_COLOR_ERROR); // SOON: Replace with custom config
	ledSetBrightness(LED_BRGHT_ERROR, 1); // SOON: Replace with custom config

	// Print RST text
	ledPrint("-RST"); // SOON: Remove "-" before RST	
}

void ledShowBLE(void)
{
	// Set BLE connection color and brightness
	LEDs.rgb(LED_COLOR_BLE_CONN); // SOON: Replace with custom config
	ledSetBrightness(LED_BRGHT_BLE_CONN, 1); // SOON: Replace with custom config

	// Print BLE text
	ledPrint("-BLE"); // SOON: Remove "-" before BLE	
}

void ledCalculateTargetBrightness(void)
{
	uint8_t diff = 0;

	// Calculate target LED brightness
	ledTargetBrightness = (uint8_t)sStd::scale<uint16_t>(ldrValue, LDR_MIN_VALUE, LDR_MAX_VALUE, LED_MIN_BRIGHTNESS, LED_MAX_BRIGHTNESS);

	// Calculate absolute difference between current and target LED brightness
	diff = sStd::abs<uint16_t>(ledTargetBrightness - ledCurrentBrightness);

	// If current vs target brightness is greater than threshold
	if (diff >= LED_UPDATE_THRESHOLD)
	{	
		log("LED brightness update\n");

		// Determine update direction
		if (ledTargetBrightness - ledCurrentBrightness > 0) ledBrightnessUpdateDir = led_update_brightness_dir_t::LED_UPDATE_POS;
			else ledBrightnessUpdateDir = led_update_brightness_dir_t::LED_UPDATE_NEG;

		// Determine update period
		ledBrightnessUpdatePeriod = LED_BRIGHTNESS_UPDATE / diff;			
	}
	else ledTargetBrightness = ledCurrentBrightness; // Make sure they are equal
}

void ledSetBrightness(uint8_t value, uint8_t setTarget)
{
	// Update current LED line brightness
	ledCurrentBrightness = value;

	// Set target brightness
	if (setTarget) ledTargetBrightness = value;

	// Set LED line brightness
	LEDs.brightness(ledCurrentBrightness);

	// Set LED line update flag
	ledUpdateFlag = 1;
}

uint8_t ledNeedUpdate(void)
{
	return ledCurrentBrightness != ledTargetBrightness;
}

void ledUpdateBrightness(void)
{
	// LED brightness update is needed
	if (ledNeedUpdate())
	{
		// It's time to update LED brightness
		if (tick - ledLastUpdateTick >= ledBrightnessUpdatePeriod)
		{	
			int8_t value = 1;

			// Update last update tick
			ledLastUpdateTick = tick;

			// If update direction is negative
			if (ledBrightnessUpdateDir == led_update_brightness_dir_t::LED_UPDATE_NEG) value = -1;

			// Set new brightness
			ledSetBrightness(ledCurrentBrightness + value, 0);
		}
	}	
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

	#ifdef DEBUG_LED
	logf("Display[time] -> \"%s\"\n", str);
	#endif // DEBUG_LED
}

static void ledDisplayDay(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	LEDs.rgb(LED_COLOR_DAY);
	snprintf(str, sizeof(str), "DAY%d", clockGetWeekDay());
	ledPrint(str);

	#ifdef DEBUG_LED
	logf("Display[day] -> \"%s\"\n", str);
	#endif // DEBUG_LED
}

static void ledDisplayDate(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	LEDs.rgb(LED_COLOR_DATE);
	snprintf(str, sizeof(str), "%02d%02d", clockGetDay(), clockGetMonth());
	ledPrint(str);

	#ifdef DEBUG_LED
	logf("Display[date] -> \"%s\"\n", str);
	#endif // DEBUG_LED
}

static void ledDisplayTemp(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	int8_t temp = 0;
	uint8_t ledDegBitmap = LED_S3 | LED_S4 | LED_S5 | LED_S6;

	TnH.temperature(temp);
	temp = sStd::limit<int8_t>(temp, 0, 99);

	LEDs.rgb(LED_COLOR_TEMP);
	snprintf(str, sizeof(str), "%02d C", temp);
	ledPrint(str);
	displayBitmap(led_panel_t::LED_PANEL3, ledDegBitmap);

	#ifdef DEBUG_LED
	logf("Display[temp] -> \"%02d°C\"\n", temp);
	#endif // DEBUG_LED
}

static void ledDsiplayRH(void)
{
	char str[7]; // 5 bytes needed. 7 bytes placed to get rid of -Wformat-truncation
	uint8_t rh = 0;

	TnH.rh(rh);
	rh = sStd::limit<uint8_t>(rh, 0, 99);

	LEDs.rgb(LED_COLOR_RH);
	snprintf(str, sizeof(str), "%02d", rh);
	ledPrint(str);
	displayPercent();

	#ifdef DEBUG_LED
	logf("Display[rh] -> \"%02d%%\"\n", rh);
	#endif // DEBUG_LED		
}



// END WITH NEW LINE
