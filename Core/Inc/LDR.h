/**
 * @file LDR.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file for module used to measure light with LD resistor.
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


#ifndef _LDR_H_
#define _LDR_H_

// ----- INCLUDE FILES
#include			<stdint.h>


/** \defgroup LDR
 * @{
 * Module for measuring light with LD resistor.
*/


// ----- FUNCTION DECLARATIONS
/**
 * @brief Start ADC conversion of voltage from LDR.
 * 
 * @return No return value.
 */
void ldrStart(void);

/**
 * @brief Get ADC value from LDR channel.
 * 
 * @param limit Set to \c 1 to limit measured value between \ref LDR_MIN_VALUE and \ref LDR_MAX_VALUE
 * @return No return value.
 */
void ldrGetValue(uint8_t limit);


// ----- EXTERNS
extern uint16_t ldrValue;


/**@}*/

#endif // _LDR_H_

// END WITH NEW LINE
