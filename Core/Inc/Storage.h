/**
 * @file Storage.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Storage header file.
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


#ifndef _STORAGE_H_
#define _STORAGE_H_

/** \addtogroup Storage
 * @{
 * Storage module for various data.
*/

// ----- INCLUDE FILES
#include			"sEEPROM.h"
#include			"config.h"


// ----- DEFINES
// EEPROM SECTORS
#define EEPROM_CONFIG_START					EEPROM_START /**< @brief EEPROM config sector start address. */
#define EEPROM_CONFIG_SIZE					128 /**< @brief EEPROM config sector size. */


extern sEEPROM EEPROMConfig;

/** @} */

#endif // _STORAGE_H_

// END WITH NEW LINE
