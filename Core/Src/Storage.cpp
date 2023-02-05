/**
 * @file Storage.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Storage translation unit.
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
#include			"Storage.h"
#include			"sEEPROM.h"
#include			"Log.h"


// ----- OBJECTS
/**
 * @brief EEPROM object for device configuration.
 * 
 * \c EEPROM_CONFIG_START "Partition" start address offset from MCU EEPROM start address.
 * \c EEPROM_CONFIG_SIZE "Partition" size in bytes.
 */
sEEPROM Config(EEPROM_CONFIG_START, EEPROM_CONFIG_SIZE);


// ----- FUNCTION DEFINITIONS
void storageInit(void)
{
	uint32_t configMark = 0;

	// Read config mark bytes
	Config.read(CFG_ADDR_MARK, &configMark, sizeof(configMark));

	if (configMark == DEVICE_CFGED_MARK)
	{
		// SOON: Add loading configuration
		logf("Reading device configuration\n");
	}
	else
	{
		logf("Device not configured!\n");

		configMark = DEVICE_CFGED_MARK;
		Config.write(CFG_ADDR_MARK, &configMark, sizeof(configMark));

		// SOON: Write default config to EEPROM

		logf("Device configured!\n");
	}
}


// END WITH NEW LINE
