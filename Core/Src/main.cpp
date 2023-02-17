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
#include			"FWConfig.h"
#include			"init.h"
#include			"sStd.h"
#include			"SHT40.h"
#include			"ProgLED.h"
#include			"sWatchdog.h"
#include			"sRTC.h"
#include			"sEEPROM.h"
#include			"sBLE.h"

#include			"LED.h"
#include			"TnH.h"
#include			"Log.h"
#include			"Clock.h"
#include			"Storage.h"
#include			"BLE.h"


// ----- STATIC FUNCTION DECLARATIONS
/**
 * @brief Get reset reason from RCC.
 * 
 * @return No return value.
 */
static void getResetReason(void);


// ----- VARIABLES
/**
 * @brief Build info struct.
 * 
 * Placed right below vector table. Section \c buildData is defined in linker file.
 * Offset is \c 0xC0
 */
const Build buildInfo __attribute__((section(".buildData"))) = {
	""FW_NAME" "FW_VER"", /**< @brief Build version. */
	HW_VER, /**< @brief Hardware version. */
	__DATE__ /**< @brief Build date. */
};

/**
 * @brief Custom stuff init flags.
 * 
 * Bit 0: Temperature & humidity sensor init.
 * Bit 1: LED line init.
 * Bit 2: BLE init.
 */
uint8_t initFlags = 0;
volatile uint8_t wakeup = 1; /**< @brief RTC wake up flag. */
uint8_t resetFlags = 0; /**< @brief Reset flags from RCC:CSR. */
volatile uint32_t tick = 0; /**< @brief System tick counter. */


// ----- OBJECTS
iDog Dog(DOG_HANDLE, DOG_RELOAD, DOG_PRESCALER, DOG_MODE);


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
	logf("\n\nFW: %s\n", buildInfo.FW);
	logf("HW: %s\n", buildInfo.HW);
	logf("Build: %s\n", buildInfo.DATE);

	// Reset reason
	getResetReason();
	logf("Reset reason: %d\n\n", resetFlags);	

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

	// Config init
	// SOON: Add default config init

	// Storage init
	storageInit();

	// LED line init
	ledInit();

	// BLE init
	bleInit();

	// Temperature & humidity sensor init
	tnhInit();

	// Clock init
	clockInit();

	// ADC
	

	// Feed the dog!
	#ifndef DEBUG
	Dog.feed();
	#endif // DEBUG	

	log("\n");

	// Lets roll!
	while (1)
	{
		// If BLE connection was altered
		if (bleConnAltered)
		{
			// Reset flag
			bleConnAltered = 0;

			// If BLE has new connection
			if (BLE.isConnected() == SBLE_OK)
			{
				log("BLE connected\n");

				// Start temperature and RH measurment
				TnH.measure(TNH_MEASURE_TYPE);

				// Just to make sure BLE will print the message below
				delay(250); // SOON: Test it for lowest value

				// Print welcome message
				BLE.printf("\n3D Clock\nFW: %s\nHW: %s\nBuild: %s\nReset: %d\n%sType help for list of commands\n", buildInfo.FW, buildInfo.HW, buildInfo.DATE, resetFlags, sClock.isSet() ? "\0" : "->> CLOCK LOST\n");

				// Get RTC time
				clockGetTime();

				// Print RTC time over BLE
				blePrintRTC();

				// Print temperature and RH
				blePrintTnH();

				// Display right aligned "BLE" (don't remove space before "BLE")
				LEDs.rgb(LED_COLOR_BLE_CONN);
				LEDs.brightness(LED_BRGHT_BLE_CONN);
				ledPrint("-BLE"); // SOON: Remove "-" before BLE						
			}
			else // BLE disconnected
			{
				log("BLE disconnected\n");

				// Reset display info to default
				Display.reset();
			}
		}

		if (wakeup)
		{
			log("RTC Wakeup\n");

			// Reset wakeup flag
			wakeup = 0;

			// Enable LDR ADC
			LL_ADC_Enable(LDR_ADC);

			// Measure LDR
			LL_ADC_REG_StartConversion(LDR_ADC);

			// Measure TnH stuff
			TnH.measure(TNH_MEASURE_TYPE);

			// Get RTC time
			clockGetTime();

			// Log RTC time
			logRTC();	

			// Log TnH stuff
			logTnH();

			 // If RTC is not set
			if (!sClock.isSet())
			{
				log("RTC not set\n");
				
				// Display right aligned "RST" (don't remove space before RST)
				LEDs.rgb(LED_COLOR_ERROR); // SOON: Replace with custom config
				LEDs.brightness(LED_BRGHT_ERROR); // SOON: Replace with custom config
				ledPrint("-RST"); // SOON: Remove "-" before RST
			}

			// Adjust LED brightness
			while (LL_ADC_REG_IsConversionOngoing(LDR_ADC));
			uint16_t ldr = sStd::limit<uint16_t, uint16_t>(LL_ADC_REG_ReadConversionData12(LDR_ADC), 60, 90);
			LL_ADC_Disable(LDR_ADC);
			uint8_t led_ldr = SSTD_SCALE(ldr, 60, 90, 1, 100);
			LEDs.brightness(led_ldr);

			// Tick display if BLE is not connected
			if (BLE.isConnected() == SBLE_NOK) Display.tick();

			// Toggle clock :
			ledSmToggle();

			// Start RTC wakeup timer
			sClock.enableWakeup(SYS_WAKEUP_CLOCK, SYS_WAKEUP);					
		}

		// SOON: Replace BLE RX with DMA
		// If BLE is connected
		if (BLE.isConnected())
		{
			// Clear override error if needed
			if (BLE_UART->ISR & USART_ISR_ORE)
			{
				BLE_UART->ICR |= USART_ICR_ORECF;
				(void)BLE_UART->RDR;
			}

			// If new byte is received
			if (BLE_UART->ISR & USART_ISR_RXNE)
			{
				// Store received char
				char tmp = BLE_UART->RDR;

				// If string end is received
				if (tmp == '\r')
				{
					// Replace \r or \n with \0 char
					BLEInput.write('\0');

					// Pass whole string to command handler

					// SOON: Echo test
					char tmpBuff[BLE_RX_BUFFER];
					BLEInput.read(tmpBuff, BLEInput.used());
					BLE.printf("echo: %s\n", tmpBuff);
				}
				else if (tmp != '\n') BLEInput.write(tmp);
			}
		}

		// Update LED display
		ledUpdate();

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
