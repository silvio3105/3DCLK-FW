/**
 * @file main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main C++ file.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

// ----- INCLUDE FILES
#include 			"main.h"
#include			"config.h"
#include			"init.h"
#include			"sStd.h"
#include			"SHT40.h"
#include			"ProgLED.h"

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

	// Watchdog init (if not debug build)
	#ifndef DEBUG
	MX_IWDG_Init();
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
		/*TnH.clear();
		TnH.measure(SHT40_meas_t::TRH_H);

		x = TnH.rh(rh);
		logf("RH[%d]: %d%%\n", x, rh);

		x = TnH.temperature(temp);
		logf("T[%d]: %d°C\n\n", x, temp);*/

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
		LL_IWDG_ReloadCounter(IWDG);
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
