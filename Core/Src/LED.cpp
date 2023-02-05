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


// ----- VARIABLES
/**
 * @brief Character bitmap array.
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
	{ '-', (LED_S6) },
	{ '\\', (LED_S3 | LED_S6 | LED_S7) },
	{ '/', (LED_S2 | LED_S5 | LED_S6) }
};

/**
 * @brief Array with start start indexes for each LED PCB.
 * 
 * @warning Array order must be: Dot, LED1, LED2, LED3 & LED4!
 */
uint8_t ledCharIdx[5] = {
	LED_IDX_DOT,
	LED_IDX_1,
	LED_IDX_2,
	LED_IDX_3,
	LED_IDX_4
};

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

void ledInit(void)
{
	// Clear LED init flag
	SSTD_BIT_CLEAR(initFlags, INIT_LED_POS);

	// Init LED line and switch result
	switch (LEDs.init())
	{
		case PROG_LED_OK:
		{
			log("LED init OK\n");
			logf("Total LEDs %d\n", LEDS);

			// Set init flag for LED line
			SSTD_BIT_SET(initFlags, INIT_LED_POS);

			// SOON: Test
			LEDs.rgb(ProgLED_rgb_t::WHITE);
			//LEDs.led[LED_IDX_DOT].rgb(0xFF0000, 42);
			//LEDs.led[LED_IDX_DOT + 1].rgb(0xFF0000, 42);
			//LEDs.off();
			LEDs.led[0].off();
			LEDs.led[1].off();
			//LEDs.led[2].on();

			ledPrint("8");

			LED_UPDATE;
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

void ledPrint(const char* c)
{
	char bitmap = 0;

	// Loop through input four characters
	for (uint8_t i = 1; i < 2; i++) // SOON: i < 5
	{
		// If NULL char is found, break
		if (!c[i - 1]) break;

		// Get bitmap for character
		bitmap = getCharBitmap(c[i - 1]);

		// Turn on or off LEDs using character bitmap
		for (uint8_t bIdx = 0; bIdx < 7; bIdx++)
		{
			if (SSTD_BIT(bitmap, bIdx)) LEDs.led[ledCharIdx[i] + bIdx].on();
				else LEDs.led[ledCharIdx[i] + bIdx].off();
		}
	}
}

void toggleSemicolon(void)
{
	// Toggle semicolon LEDs
	LEDs.led[LED_IDX_DOT].toggle();
	LEDs.led[LED_IDX_DOT + 1].toggle();
}

// END WITH NEW LINE
