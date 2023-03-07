/**
 * @file sRTT.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief RTT header file.
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


#ifndef _SRTT_H_
#define _SRTT_H_

// ----- INCLUDE FILES
#include			"SEGGER_RTT.h"
#include			"sStd.h"

#include			<stdio.h>
#include			<stdarg.h>


/** \addtogroup sRTT
 * @{
 * Simple RTT.
*/

// ----- CLASSES
/**
 * @brief Simple RTT class.
 * 
 * @tparam size Size of buffer used for \ref sRTT::printf method.
 */
template<uint16_t size>
class sRTT {
	// PUBLIC STUFF
	public:
	// CONSTRUCTOR AND DECONSTRUCTOR DECLARATIONS
	/**
	 * @brief Object contrcutor.
	 * 
	 * @param ch RTT output channel.
	 * @return No return value.
	 */
	sRTT(uint8_t ch)
	{
		// Null buffer
		buff[0] = '\0';

		// Set RTT channel
		channel = ch;
	}

	/**
	 * @brief Object deconstructor.
	 * 
	 * @return No return value.
	 */
	~sRTT(void)
	{
		// Reset to default values
		buff[0] = '\0';
		channel = 0;
	}

	// METHOD DECLARATIONS
	/**
	 * @brief Print string to RTT.
	 * 
	 * @param str Pointer to C-string to print.
	 * @return No return value.
	 */
	inline void print(const char* str)
	{
		// Write string to RTT channel
		SEGGER_RTT_Write(channel, str, sStd::len(str));
	}

	/**
	 * @brief Print string to RTT.
	 * 
	 * @param str Pointer to C-string to print.
	 * @param len Length of \c str
	 * @return No return value.
	 */
	inline void print(const char* str, uint16_t len)
	{
		// Write string to RTT channel
		SEGGER_RTT_Write(channel, str, len);
	}	

	/**
	 * @brief Format and print string to RTT.
	 * 
	 * @param str Pointer to C-string to format and print.
	 * @param ... String arguments.
	 * @return No return value.
	 */
	void printf(const char* str, ...)
	{
		// Start variadic argument list
		va_list agrs;
		va_start(agrs, str);

		// Format string with arguments
		uint16_t len = vsnprintf(buff, sizeof(buff), str, agrs);

		// Print formated string to RTT
		print(buff, len);

		// End variadic argument list
		va_end(agrs);
	}


	// PRIVATE STUFF
	private:
	// VARIABLES
	char buff[size] = { '\0' }; /**< @brief Buffer for \ref printf method. */
	uint8_t channel = 0; /**< @brief RTT channel where strings will be printed. */
};


/**@}*/

#endif // _SRTT_H_

// END WITH NEW LINE
