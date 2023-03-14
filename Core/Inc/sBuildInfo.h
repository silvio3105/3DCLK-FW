/**
 * @file sBuildInfo.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Simple Build Info library header file.
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


#ifndef _SBUILDINFO_H_
#define _SBUILDINFO_H_


/** \addtogroup sBuildInfo 
 * Simple Build Info library
 * 
 * User must ensure \c buildInfo section exist in linker file.
 * @{
*/


// ----- CODE SNIPPETS
/**
 * @brief Code snippet for creating build info struct in flash memory.
 * 
 * Struct is placed inside \c buildInfo section in flash memory.
 * 
 * @param _name Firmware name. Max 16 chars.
 * @param _ver Firmware version. Max 16 chars.
 * @param _rev Hardware revision. Max 16 chars.
 * @param _date Build date. Max 16 chars.
 */
#define SBUILD(_name, _ver, _rev, _date) \
	const build_info_t buildInfo __attribute__((section(".buildInfo"))) = { \
		_name, \
		_ver, \
		_rev, \
		_date \
	}

#define SBUILD_NAME			buildInfo.fwName /**< @brief Code snippet for build firmware name. */
#define SBUILD_VER			buildInfo.fwVer /**< @brief Code snippet for build firmware version. */
#define SBUILD_REV			buildInfo.hwRev /**< @brief Code snippet for build hardware revision. */
#define SBUILD_DATE			buildInfo.buildDate /**< @brief Code snippet for build date. */


// ----- STRUCTS
/**
 * @brief Struct for build info.
 * 
 */
struct build_info_t {
	char fwName[16]; /**< @brief C-string for firmware name. */
	char fwVer[16]; /**< @brief C-string for firmware version. */
	char hwRev[16]; /**< @brief C-string for hardware revision. */
	char buildDate[16]; /**< @brief C-string for build date. */
};


// ----- EXTERNS
extern const build_info_t buildInfo;


/** @} */


#endif // _SBUILDINFO_H_

// END WITH NEW LINE
