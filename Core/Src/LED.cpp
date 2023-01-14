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
#include			"config.h"
#include			"sStd.h"
#include			"ProgLED.h"

#include			"Log.h"


// ----- DEFINES
/**
 * @brief Snippet for calling LED line update.
 * 
 */
#define LED_UPDATE \
	LEDs.update(LED_LINE)


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


// ----- EXTERNS
extern sStd::Logger<LOG_BUFF> Serial;
extern uint8_t initFlags;


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
			logf("Total LEDs %d. LED init OK\n", LEDS);

			// Set init flag for LED line
			SSTD_BIT_SET(initFlags, INIT_LED_POS);

			// SOON: Test
			LEDs.rgb(ProgLED_rgb_t::NEON_GREEN);
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

// END WITH NEW LINE
