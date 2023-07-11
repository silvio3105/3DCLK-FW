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
#include			"sBuildInfo.h"
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
#include			"LDR.h"


// ----- STATIC FUNCTION DECLARATIONS
/**
 * @brief Get reset reason from RCC.
 * 
 * @return No return value.
 */
static void getResetReason(void);


// ----- VARIABLES
/**
 * @brief Build info struct in flash memory.
 * 
 * Placed right below vector table. Offset is \c 0xC0
 */
SBUILD(FW_NAME, FW_VER, HW_REV, __DATE__);


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
/**
 * @brief Watchdog object.
 * 
 * Max was The Dog. The Dog of all dogs.
 * He was two days from 15th birthday when he went to sleep for ever.
 * Now, he's only task is, besides being a good boi, to cool down MCU with his tail so it does not overheat and stuck.
 */
iDog Max(DOG_HANDLE, DOG_RELOAD, DOG_PRESCALER, DOG_MODE);

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%(/******/&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@(,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,,,,,,,,,,,,,,,,,*(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,,,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,****,,,,,,,,%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,,*,,*,,,,,,,,/,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,**,,,,,,,*,,,*,,,**,&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@/,,,,,,,,,,,,*,,,,,,,,,****,,,,,,,,,,,,,*,,,,,***,,,,,*,,,*,,,*,,*(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@,,*,,,,,,,,,*****#&@@@&#/**,,,,,,,,***//**,,******,,,**,,*******,#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@%,*,,,,,,,*/****/%&&@&((/,,,,,,,,,*/%&@@@@@%////***,***********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@#,,,,,,,/***,,*****((**,**,,,,,*//(&%&&%(**//****,****////**/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@(,,,*((**,,,,,,,,(,,,,,,,,*,,,**%/***/**,/***/(,****///******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@/,*(#((/*,,,,,,,*,,,,,***,*,,,,*(/***,,,,////(#/,************/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@(((/*,,,,,,,,,,,,********,,**/**,,,,*////(##/*******/*////**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@&/*///**,,,,,,,,,**//////***,,****,,,**////(((/*/(*//*/////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@#****/*/*,,,,,**(###(#####(/*********/////////(//**////*//////**(%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@**********,,,,*##((#######%#/******/(((/////*(////*//////////////***///***************/***/%@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@***********,***#%%(((((##%%%/****//(((((((((//////**/////////////**********************/(%@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@***********,***(%#@&&%@@&&&/*****//**/(((((///////**/////////**((/////*********/#&@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@(,**************/#%&&@@@&&(//*****/***/((((////////**///////***/@@@@&&&&&@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@*,,,,******/*//*/#%&&#&&%##///////*////(///////***/**///////*/*/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@,,,,,*******/(####(#%%%#####((((////////////*****//**///////***/&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@#,,,,,,,,******/((((###########((((////////*//*****/***/////****(&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@,,,,,,,,,,*******/(((((((######((((((//////*******/****////****/(/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@/,,,,,,,,,,,********//((((((###(((((////////*******/////(//////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,*,********//(((%%##(((((((//////******//**////////////#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@,,,,,,,,,,,,,,,**///**////((###(((((//////////*////////////////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@&,,,,,,,,,,,,,,,,***//(/(((/((((((((//////(//////(((#@@#((((///((((#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,******//////((((((//////((((((((((@@@@&&#((((((((//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,,,,,,,******/////(((/(///////////////&@@@@@@&&#((((((/(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,***,,,,***//*****////(///(((((/////////@@@@@@@@@@@@%##(/(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,***%@@@@@@@#*****/(@@@@#/(#(////*///#@@@@@@@@@@@@@&%#(#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@*,,,,,,,,,,,,,**@@@@@@@@@@#*//&@@@@@@@%((//*****/#@@@@@@@@@@@@@@%%#((*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@(,,,,,,,,,,,,,*(@@@@@@@@@@@@@@@@@@@@@@((//****///@@@@@@@@@@@@@&%#((/(*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@/,,,,,,*,,,,,,*&@@@@@@@@@@@@@@@@@@@@@/(/*****///@@@@@@@@@@@@@@&((((((%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@/,,,,,**,,,,,,/@@@@@@@@@@@@@@@@@@@@@@(*****///%@@@@@@@@@@@@@@@(##(##%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@%*,,,,,**,,,,,*&@@@@@@@@@@@@@@@@@@@@@(*****///@@@@@@@@@@@@@@@@@@%##%&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@/*,,,,,**,,,,,%@@@@@@@@@@@@@@@@@@@@@(******/(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@(,,,,,,*,,,,,#@@@@@@@@@@@@@@@@@@@@@/******//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@/,,,,,****,,/@@@@@@@@@@@@@@@@@@@@&**,****/(#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@,,,,,,****,,@@@@@@@@@@@@@@@@@@@@/******/*/%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@,,,,*****,,&@@@@@@@@@@@@@@@@@@@&/*******(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@#**,,*****,&@@@@@@@@@@@@@@@@@@@@********%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@,*********#@@@@@@@@@@@@@@@@@@@%***,,,,,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@&********//@@@@@@@@@@@@@@@@@@@#***,,,,*,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@/********(#@@@@@@@@@@@@@@@@@@&//****,**,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@*********/(@@@@@@@@@@@@@@@@//((////*****,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@&*********/@@@@@@@@@@@@@@@@%%((((///**(***@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@**,**,,***/@@@@@@@@@@@@@@@@@&(((#///*//#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@**,,******,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@%*,,,,,******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@,,,,*******##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@,,,*********(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@#*************#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@%///**//////***%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@#////////(//////#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@///////((#%//%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@#((///(((##&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@((((&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



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
	Max.start();
	#endif // DEBUG

	// Debug UART init
	MX_USART2_UART_Init();	

	// Set logger status if not DEBUG build
	#ifdef DEBUG
	Serial.status(sStd::logStatus_t::LOG_ON);
	#endif // DEBUG

	// Firmware and hardware info
	logf("\n\nFW: %s\n", SBUILD_VER);
	logf("HW: %s\n", SBUILD_REV);
	logf("Build: %s\n", SBUILD_DATE);

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
	

	log("\n");

	// Display right aligned RST text if RTC is not set
	if (!sClock.isSet()) ledShowRST();

	// Set BLE module into sleep mode
	BLE.sleep();	

	// Feed the dog!
	#ifndef DEBUG
	Max.feed();
	#endif // DEBUG

	// Enable RTC wake up
	sClock.wakeupEnable(SYS_WAKEUP_CLOCK);

	log("Roll!\n");

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

				// Get RTC time
				clockGetTime();

				// Display right aligned BLE text
				ledShowBLE();	

				// Just to make sure BLE will print the message below
				delay(250); // SOON: Test it for lowest value

				// Print welcome message
				BLE.printf("\n3D Clock\nFW: %s\nHW: %s\nBuild: %s\nReset: %d\n%sType help for list of commands\n", SBUILD_NAME, SBUILD_REV, SBUILD_DATE, resetFlags, sClock.isSet() ? "\0" : "->> CLOCK LOST\n");

				// Print RTC time over BLE
				blePrintRTC();

				// Print temperature and RH
				blePrintTnH();				
			}
			else // BLE disconnected
			{
				log("BLE disconnected\n");

				// Reset display info to default is RTC is set
				if (sClock.isSet()) Display.reset();
					else ledShowRST(); // Display RST

				// Set BLE module into sleep mode
				BLE.sleep();
			}
		}

		// SOON: Plan is to use sleep. Plan.
		// If wake up flag is set
		if (wakeup)
		{
			// Start RTC wakeup timer
			sClock.wakeupStart(SYS_WAKEUP);			

			// Reset wakeup flag
			wakeup = 0;

			// Decrease TnH tick
			tnhTicks--;

			// Measure TnH stuff if tick is zero
			if (!tnhTicks)
			{
				// Reset tick counter to default value
				tnhTicks = TNH_TICKS;

				// Start TnH measure
				TnH.measure(TNH_MEASURE_TYPE);
			}

			// Print TnH stuff if TnH BLE print is enabled
			if (blePrintTnHFlag) blePrintTnH();

			 // If RTC is set
			if (sClock.isSet())
			{
				// Start LDR voltage measure
				ldrStart();

				// Get RTC time
				clockGetTime();

				// Log RTC time
				#ifdef DEBUG_WAKEUP
				logRTC();
				#endif // DEBUG_WAKEUP

				// Print RTC over BLE is RTC BLE print is enabled
				if (blePrintRTCFlag) blePrintRTC();

				// Tick display if BLE is not connected
				if (BLE.isConnected() == SBLE_NOK) Display.tick();

				// Get value from LDR - must call before ledCalculateTargetBrightness function
				ldrGetValue(1);

				// Calculate new LED brightness
				ledCalculateTargetBrightness();				
			}

			// Log TnH stuff
			#ifdef DEBUG_WAKEUP
			logTnH();		
			#endif // DEBUG_WAKEUP	

			// Toggle clock :
			ledSmToggle();

			// Keep watchdog feed inside wakeup check - MCU will reset if RTC wakeup fail
			// Feed the Good boy!
			#ifndef DEBUG
			Max.feed();
			#endif // DEBUG			
		}

		// Update LED brightness
		ledUpdateBrightness();

		// Update LED display
		ledUpdate();

		// Get character over UART if BLE has connection
		if (BLE.isConnected()) bleGetChar();
		else // BLE has no connection
		{
			// If LED line is in idle state and brightness update is not needed
			if (LEDs.status() == ProgLED_state_t::IDLE && !ledNeedUpdate())
			{
				//log("DMX!\n\n");

				// SOON: Put MCU into sleep mode
			}
		}
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
