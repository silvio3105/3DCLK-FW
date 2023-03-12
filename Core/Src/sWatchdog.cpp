/**
 * @file sWatchdog.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Watchdog translation unit.
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
#include			"sWatchdog.h"


// ----- METHOD DEFINITIONS
// STM32L051 INDEPENDENT WATCHDOG
#ifdef STM32L051xx

iDog::iDog(IWDG_TypeDef* iDogHandle, uint16_t reloadValue, iDog_prescaler_t prescaleValue, iDog_mode_t mode)
{
	// Set watchdog handle
	handle = iDogHandle;

	// Set watchdog prescaler
	setPrescaler(prescaleValue);

	// Set watchdog reload value
	setReloadValue(reloadValue);

	// Set watchdog behaviour when core is halted
	if (mode == DBG_HALT)
	{
		// Enable clock for DBGMCU
		RCC->APB2ENR |= RCC_APB2ENR_DBGEN;

		// Disable IWDG when core is halted
		DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;

		// Disable clock for DBGMCU
		RCC->APB2ENR &= ~RCC_APB2ENR_DBGEN;
	}
}

iDog::~iDog(void)
{
	// Set watchdgo handle to NULL
	handle = nullptr;
}


void iDog::setPrescaler(iDog_prescaler_t value)
{
	// Wait if prescaler update is ongoing
	while (handle->SR & IWDG_SR_PVU);

	// Enable write access
	access();

	// Write prescaler value
	handle->PR = value;

	// Feed watchdog
	feed();
}

void iDog::setReloadValue(uint16_t value)
{
	// Wait if reload value update is ongoing
	while (handle->SR & IWDG_SR_RVU);

	// Enable write access
	access();

	// Make sure value does not exceed value defined with IDOG_MAX_RELOAD
	if (value > IDOG_MAX_RELOAD) value = IDOG_MAX_RELOAD;

	// Write reload value
	handle->RLR = value;

	// Feed watchdog
	feed();
}

#endif // STM32L051xx


// END WITH NEW LINE
