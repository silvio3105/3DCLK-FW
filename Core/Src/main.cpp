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
#include			"sRTC.h"
#include			"sEEPROM.h"

#include			"LED.h"
#include			"TnH.h"
#include			"Log.h"
#include			"Clock.h"
#include			"Storage.h"


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


volatile uint8_t time = 0;
volatile uint32_t tick = 0;

// ----- APPLICATION ENTRY POINT
int main(void)
{
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

	// Debug UART init
	MX_USART2_UART_Init();	

	// Set logger status if not DEBUG build
	#ifdef DEBUG
	Serial.status(sStd::logStatus_t::LOG_ON);
	#endif // DEBUG

	// Firmware and hardware info
	logf("FW: %s\n", buildInfo.FW);
	logf("HW: %s\n", buildInfo.HW);
	logf("Build: %s\n", buildInfo.DATE);

	// Reset reason
	getResetReason();
	logf("Reset reason: %d\n", resetFlags);	

	// GPIO init
	MX_GPIO_Init();

	// DMA init
	MX_DMA_Init();

	// ADC init
	MX_ADC_Init();

	// IC21 init
	MX_I2C1_Init();

	// Timer2 init
	MX_TIM2_Init();

	// BLE UART init
	MX_USART1_UART_Init();

	// Give 1s to make sure other ICs are on
	#ifndef DEBUG
	delay(1000);
	#endif // DEBUG

	// LED line init
	ledInit();

	// Temperature & humidity sensor init
	tnhInit();

	// Clock init
	clockInit();


	// EEPROM TEST
	uint32_t val[] = { 1, 10, 100, 0, 127 };
	//EEPROMConfig.write(0, val, sizeof(val));
	memset(val, 0xFF, sizeof(val));
	EEPROMConfig.read(0, val, sizeof(val));
	log("\n");
	for (uint8_t i = 0; i < 5; i++) logf("- Value %d: %d\n", i + 1, val[i]);
	//EEPROMConfig.erase(0, 1);
	memset(val, 0xFF, sizeof(val));
	EEPROMConfig.read(0, val, sizeof(val));
	for (uint8_t i = 0; i < 5; i++) logf("- Value %d: %d\n", i + 1, val[i]);
	log("\n");


	// ADC
	LL_ADC_Enable(ADC1);


	uint8_t x = 100;
	uint8_t rh = 0;
	int16_t temp = 0;

	// Feed the dog!
	#ifndef DEBUG
	Dog.feed();
	#endif // DEBUG	

	static const char days[7][4] = {
		"Mon",
		"Tue",
		"Wed",
		"Thu",
		"Fri",
		"Sat",
		"Sun"
	};

	static const char pm[2][3] = {
		"AM",
		"PM"
	};

	sRTC_time_t c;
	sClock.enableWakeup(sRTC_WUT_clock_t::CK_SPRE, 10);

	while (1)
	{
		if (time)
		{
			/*time = 0;

			sClock.get(c);
			logf("Date: %s %02d.%02d.%04d.\n", days[c.weekDay - 1], c.day, c.month, c.year + 2000);
			logf("Time: %02d:%02d:%02d %s\n", c.hour, c.minute, c.second, pm[c.ampm]);	


			TnH.clear();
			TnH.measure(SHT40_meas_t::TRH_H);

			x = TnH.rh(rh);
			logf("RH[%d]: %d%%\n", x, rh);

			x = TnH.temperature(temp);
			logf("T[%d]: %d°C\n\n", x, temp);
*/

			//sClock.enableWakeup(sRTC_WUT_clock_t::CK_SPRE, 10);
		}	

		LL_ADC_REG_StartConversion(ADC1);
		while (LL_ADC_REG_IsConversionOngoing(ADC1));
		uint16_t ldr = LL_ADC_REG_ReadConversionData12(ADC1);
		logf("LDR: %d\n", ldr);

		ldr = sStd::scale<uint16_t>(ldr, 60, 600, 1, 100);

		LEDs.brightness(ldr);
		LEDs.update(LED_LINE);

		delay(100);		

		// Feed the dog!
		#ifndef DEBUG
		Dog.feed();
		#endif // DEBUG
	}
}


// ----- FUNCTION DEFINITIONS
static void getResetReason(void)
{
	// Get reset flags from control status register
	resetFlags = (RCC->CSR & (0xFF << 24)) >> 24;

	// Reset control status register
	RCC->CSR |= RCC_CSR_RMVF;
}

// END WITH NEW LINE
