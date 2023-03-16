/**
 * @file LDR.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Module for measuring light with LD resistor.
 * 
 * @copyright Copyright (c) 2023
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
#include			"LDR.h"
#include			"main.h"
#include 			"FWConfig.h"
#include			"sStd.h"

#include			<stdint.h>


// ----- VARIABLES
uint16_t ldrValue = 0; /**< @brief Current LDR ADC value. */


// ----- FUNCTION DEFINITIONS
void ldrStart(void)
{
	// Enable LDR ADC
	LL_ADC_Enable(LDR_ADC);

	// Start ADC conversion LDR
	LL_ADC_REG_StartConversion(LDR_ADC);
}

void ldrGetValue(void)
{
	// Wait if conversion is not done yet
	while (LL_ADC_REG_IsConversionOngoing(LDR_ADC));

	// Get ADC value
	ldrValue = LL_ADC_REG_ReadConversionData12(LDR_ADC);

	// Limit LDR value between minimum and maximum expected LDR value
	ldrValue = sStd::limit<uint16_t, uint16_t>(ldrValue, LDR_MIN_VALUE, LDR_MAX_VALUE);	

	// Disable ADC
	LL_ADC_Disable(LDR_ADC);
}


// END WITH NEW LINE
