/**
 * @file TnH.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Hader file for temperature & humidity sensor module.
 * @date 08.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _TNH_H
#define _TNH_H

// ----- INCLUDE FILES
#include			"main.h"
#if (TNH_SENSOR == SHT40_AD) || (TNH_SENSOR == SHT40_B)
#include			"SHT40.h"
#endif // TNH_SENSOR


// ----- FUNCTION DECLARATIONS
/**
 * @brief Temperature & humidity sensor init.
 * 
 * @return No return value.
 */
void tnhInit(void);


// ----- EXTERNS
#if (TNH_SENSOR == SHT40_AD) || (TNH_SENSOR == SHT40_B)
extern SHT40 TnH;
#endif // TNH_SENSOR


#endif // _TNH_H

// END WITH NEW LINE