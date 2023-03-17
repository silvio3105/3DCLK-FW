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
 * Library can be used only with GCC toolchain.
 * User must ensure \c buildInfo section exists in linker file.
 * @{
*/


// ----- CODE SNIPPETS
/**
 * @brief Code snippet for creating build info data in flash memory.
 * 
 * Data is placed inside \c buildInfo section in flash memory.
 * 
 * @param _name Firmware name. Max 16 chars.
 * @param _ver Firmware version. Max 16 chars.
 * @param _rev Hardware revision. Max 16 chars.
 * @param _date Build date. Max 12 chars.
 */
#define SBUILD(_name, _ver, _rev, _date) \
	const build_info_t buildInfo __attribute__((section(".buildInfo"))) = { \
		_name, \
		_ver, \
		_rev, \
		_date \
	}

/**
 * @brief Code snippet for creating build info data in flash memory.
 * 
 * With this snippet, firmware name is replaced with firmware tag and variant, both 8 characters long.
 * Data is placed inside \c buildInfo section in flash memory.
 * 
 * @param _tag Firmware tag. Max 8 chars.
 * @param _variant Firmware variant. Max 8 chars.
 * @param _ver Firmware version. Max 16 chars.
 * @param _rev Hardware revision. Max 16 chars.
 * @param _date Build date. Max 12 chars.
 * 
 * @warning GCC 11.3+ is needed for this snippet.
 */
#define SBUILD_EXT(_tag, _variant, _ver, _rev, _date) \
	const build_info_t buildInfo __attribute__((section(".buildInfo"))) = { \
		{ \
			.tag = _tag, \
			_variant \
		}, \
		_ver, \
		_rev, \
		_date \
	}

#define SBUILD_NAME			buildInfo.fw.name /**< @brief Code snippet for firmware build name. */
#define SBUILD_TAG			buildInfo.fw.tag /**< @brief Code snippet for firmware tag used in build. */
#define SBUILD_VARIANT		buildInfo.fw.variant /**< @brief Code snippet for firmware variant used in build. */
#define SBUILD_VER			buildInfo.fwVer /**< @brief Code snippet for firmware build version. */
#define SBUILD_REV			buildInfo.hwRev /**< @brief Code snippet for hardware build revision. */
#define SBUILD_DATE			buildInfo.buildDate /**< @brief Code snippet for build date. */


// ----- STRUCTS
/**
 * @brief Struct for build info.
 * 
 */
struct build_info_t {
	/**
	 * @brief Union of firmware name, tag and variant.
	 * 
	 */
	union {
		const char name[16]; /**< @brief C-string for firmware name. */
		struct {
			const char tag[8]; /**< @brief C-string for firmware tag. */
			const char variant[8]; /**< @brief C-string for firmware variant name. */
		};
	} fw;
	const char fwVer[16]; /**< @brief C-string for firmware version. */
	const char hwRev[16]; /**< @brief C-string for hardware revision. */
	const char buildDate[12]; /**< @brief C-string for build date. */
};


// ----- EXTERNS
extern const build_info_t buildInfo;


/** @} */


#endif // _SBUILDINFO_H_

// END WITH NEW LINE
