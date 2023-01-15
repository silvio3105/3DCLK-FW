/**
 * @file main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main C++ file.
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
#include 			"main.h"
#include			"config.h"
#include			"init.h"
#include			"sStd.h"
#include			"SHT40.h"
#include			"ProgLED.h"
#include			"sWatchdog.h"

#include			"LED.h"
#include			"TnH.h"
#include			"Log.h"


// ----- VARIABLES
/**
 * @brief Build info struct.
 * 
 * Placed right below vector table. Section \c buildData is defined in linker file.
 * Offset is \c 0xC0
 */
const Build buildInfo __attribute__((section(".buildData"))) = {
	FW_VER, /**< @brief Firmware version string. */
	HW_VER, /**< @brief Hardware version string. */
	__DATE__ /**< @brief Build date. */
};

/**
 * @brief Custom stuff init flags.
 * 
 * Bit 0: Temperature & humidity sensor init.
 * Bit 1: LED line init.
 */
uint8_t initFlags = 0;
uint8_t resetFlags = 0; /**< @brief Reset flags from RCC:CSR. */

// ----- OBJECTS
// Watchdog object
iDog Dog(DOG_HANDLE, DOG_RELOAD, DOG_PRESCALER, DOG_MODE);


// ----- STATIC FUNCTION DECLARATIONS
/**
 * @brief Get reset reason from RCC.
 * 
 * @return No return value.
 */
static void getResetReason(void);


// ----- APPLICATION ENTRY POINT
int main(void)
{
	// STM32 INIT
	// Enable clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	// Set SysTick interrupt priority
	NVIC_SetPriority(SysTick_IRQn, 3);

	// Configure system clock
	SystemClock_Config();

	// Watchdog init (if not debug build)
	#ifndef DEBUG
	Dog.start();
	#endif // DEBUG  	

	// GPIO init
	MX_GPIO_Init();

	// DMA init
	MX_DMA_Init();

	// ADC init
	MX_ADC_Init();

	// IC21 init
	MX_I2C1_Init();

	// RTC init
	MX_RTC_Init();

	// Timer2 init
	MX_TIM2_Init();

	// UARTs init
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();

	// Give 1s to make sure other ICs are on
	#ifndef DEBUG
	delay(1000);
	#endif // DEBUG


	// Firmware and hardware info
	logf("FW: %s\n", buildInfo.FW);
	logf("HW: %s\n", buildInfo.HW);
	logf("Build: %s\n", buildInfo.DATE);

	// Reset reason
	getResetReason();
	logf("Reset reason: %d\n", resetFlags);


	// MODULES INIT
	// LED line init
	ledInit();

	// Temperature & humidity sensor init
	tnhInit();





	uint8_t x = 100;
	uint8_t rh = 0;
	int16_t temp = 0;

	while (1)
	{
		TnH.clear();
		TnH.measure(SHT40_meas_t::TRH_H);

		x = TnH.rh(rh);
		logf("RH[%d]: %d%%\n", x, rh);

		x = TnH.temperature(temp);
		logf("T[%d]: %d°C\n\n", x, temp);

		/*for (uint8_t b = 0; b < 255; b++)
		{
			for (uint8_t g = 0; g < 255; g++)
			{
				for (uint8_t r = 0; r < 255; r++)
				{
					LEDs.rgb(r, g, b);
					LEDs.update(LED_LINE);
					delay(2);
				}			
			}			
		}

		delay(5000);*/

		for(uint8_t i = 0; i < 13; i++)
		{
			LEDs.brightness(i);
			LEDs.update(LED_LINE);
			delay(10);
		}

		delay(1000);

		for(int8_t i = 13; i > -1; i--)
		{
			LEDs.brightness(i);
			LEDs.update(LED_LINE);
			delay(10);
		}		

		delay(1000);

		// Feed the dog!
		#ifndef DEBUG
		Dog.feed();
		#endif // DEBUG
	}
}


// ----- FUNCTION DEFINITIONS
void getResetReason(void)
{
	resetFlags = (RCC->CSR & (0xFF << 24)) >> 24;
	RCC->CSR |= RCC_CSR_RMVF;
}

// END WITH NEW LINE
