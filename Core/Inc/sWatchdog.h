/**
 * @file sWatchdog.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Watchdog header file.
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


#ifndef _SWATCHDOG_H_
#define _SWATCHDOG_H_

/** \addtogroup sWatchdog
 * @{
 * Simple watchdog driver.
*/

// STM32L051
#ifdef STM32L051xx

/** \defgroup STM32L051
 * @{
 * Watchdog for STM32L051 MCU.
*/

// ----- INCLUDE FILES
#include			<stm32l051xx.h>
#include			<system_stm32l0xx.h>


// ----- DEFINES
#define IDOG_KEY_REL				0xAAAA /**< @brief IWDG reload key. */
#define IDOG_KEY_ACCESS				0x5555 /**< @brief IWDG access key. */
#define IDOG_KEY_START				0xCCCC /**< @brief IWDG start key. */
#define IDOG_MAX_RELOAD				4095 /**< @brief Maximum reload value. */


// ----- ENUMS
/**
 * @brief IWDG mode enum.
 * 
 */
enum iDog_mode_t : uint8_t {
	DBG_CONTINUE = 0, /**< @brief IWDG will continue to work even if core is halted. */
	DBG_HALT = 1 /**< @brief IWDG will stop if core is halted. */
};

enum iDog_prescaler_t : uint8_t {
	DIV4 = 0b000, /**< @brief IWDG clock prescaler 4. */
	DIV8 = 0b001, /**< @brief IWDG clock prescaler 8. */
	DIV16 = 0b010, /**< @brief IWDG clock prescaler 16. */
	DIV32 = 0b011, /**< @brief IWDG clock prescaler 32. */
	DIV64 = 0b100, /**< @brief IWDG clock prescaler 64. */
	DIV128 = 0b101, /**< @brief IWDG clock prescaler 128. */
	DIV256 = 0b110 /**< @brief IWDG clock prescaler 256. */
};


// ----- CLASSES
// INDEPENDENT WATCHDOG CLASS
/**
 * @brief STM32 IWDG class.
 * 
 */
class iDog {
	// PUBLIC STUFF
	public:
	// OBJECT CONSTRUCTOR AND DECONSTRUCTOR
	/**
	 * @brief iDog object constructor.
	 * 
	 * @param iDogHandle Pointer to handle for STM32 IWDG.
	 * @param reloadValue Watchdog reload value. Maximum value is defined with \ref IDOG_MAX_RELOAD
	 * @param prescaleValue Watchdog clock prescaler. See \ref iDog_prescaler_t
	 * @param mode Watchdog mode. This parameter is optional. See \ref iDog_mode_t
	 * @return No return value.
	 */
	iDog(IWDG_TypeDef* iDogHandle, uint16_t reloadValue, iDog_prescaler_t prescaleValue, iDog_mode_t mode = iDog_mode_t::DBG_CONTINUE);

	/**
	 * @brief iDog object deconstructor.
	 * 
	 * @return No return value.
	 */
	~iDog(void);


	// METHODS
	/**
	 * @brief Start watchdog.
	 * 
	 * @return No return value.
	 */
	inline void start(void)
	{
		// Write start key to start watchdog
		handle->KR = IDOG_KEY_START;
	}

	/**
	 * @brief Feed(reload) watchdog.
	 * 
	 * @return No return value.
	 */
	inline void feed(void)
	{
		// Write reload key to reload watchdog counter and prevent watchdog reset
		handle->KR = IDOG_KEY_REL;
	}

	/**
	 * @brief Set watchdog clock prescaler.
	 * 
	 * @param value New clock prescaler. See \ref iDog_prescaler_t
	 * @return No return value.
	 */
	void setPrescaler(iDog_prescaler_t value);

	/**
	 * @brief Set watchdog reload value.
	 * 
	 * @param value No watchdog reload value.
	 * @return No return value.
	 */
	void setReloadValue(uint16_t value);	


	// PRIVATE STUFF
	private:
	// VARIABLES
	IWDG_TypeDef* handle = nullptr; /**< @brief STM32 IWDG handle. */

	// METHODS
	/**
	 * @brief Enable register write access.
	 * 
	 * @return No return value.
	 */
	inline void access(void)
	{
		// Write access value to KR register to unlock register protection
		handle->KR = IDOG_KEY_ACCESS;
	}
};

/**@}*/

#endif // STM32L051xx

/**@}*/

#endif // _SWATCHDOG_H_

// END WITH NEW LINE
