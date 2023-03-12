/**
 * @file sADC.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Simple ADC driver header file.
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

#ifndef _SADC_H_
#define _SADC_H_

/** \addtogroup sADC
 * @{
 * Simple ADC driver.
*/

// STM32L051
#ifdef STM32L051xx

/** \defgroup STM32L051
 * @{
 * ADC for STM32L051 MCU.
*/


// ----- INCLUDE FILES
#include			<stm32l051xx.h>
#include			<system_stm32l0xx.h>

// ----- CLASSES
class sADC {
	// PUBLIC STUFF
	public:
	// OBJECT CONSTRUCTORS AND DECONSTRUCTORS
	/**
	 * @brief Object constructor.
	 * 
	 * @param adcHandle Pointer to peripheral memory for ADC.
	 * @return No return value.
	 */
	sADC(ADC_TypeDef* adcHandle);

	/**
	 * @brief Object deconstructor.
	 * 
	 * @return No return value.
	 */
	~sADC(void);


	// PRIVATE STUFF
	private:
	// VARIABLES
	ADC_TypeDef* handle = nullptr; /**< @brief ADC handle. */
};


/**@}*/

#endif // STM32L051xx

/**@}*/

#endif // _SADC_H_

// END WITH NEW LINE
