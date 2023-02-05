/**
 * @file Log.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Translation unit for log module.
 * @date 08.01.2023
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
#include			"Log.h"


// ----- FUNCTION DECLARATIONS
#ifdef DEBUG
/**
 * @brief Handler for transmitting characters over UART.
 * 
 * @param buffer Pointer to C-string to transmit.
 * @param len Length of \c buffer
 * @return No return value.
 */
static void UART2Out(const char* buffer, const uint16_t len);
#endif // DEBUG


// ----- OBJECTS
#ifdef DEBUG
/**
 * @brief Logger object.
 * 
 * \c LOG_BUFF Buffer size.
 * \c UART2Out Function for handling UART2 transmits.
 * \c [DEBUG] Logger prefix.
 */
sStd::Logger<LOG_BUFF> Serial = sStd::Logger<LOG_BUFF>(UART2Out);
#endif // DEBUG


// ----- FUNCTION DEFINITIONS
#ifdef DEBUG
static void UART2Out(const char* buffer, const uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		// Wait for transfer complete flag
		while (!(USART2->ISR & USART_ISR_TC)); 

		// Clock out data
		USART2->TDR = buffer[i];
	}
}
#endif // DEBUG



// END WITH NEW LINE
