/**
 * @file Log.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Translation unit for log module.
 * @date 08.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// ----- INCLUDE FILES
#include			"Log.h"


// ----- FUNCTION DECLARATIONS
/**
 * @brief Handler for transmitting characters over UART.
 * 
 * @param buffer Pointer to C-string to transmit.
 * @param len Length of \c buffer
 * @return No return value.
 */
static void UART2Out(const char* buffer, const uint16_t len);


// ----- OBJECTS
#ifdef DEBUG
sStd::Logger<LOG_BUFF> Serial = sStd::Logger<LOG_BUFF>(UART2Out, "[DEBUG] ");
#endif // DEBUG


// ----- FUNCTION DEFINITIONS
#ifdef DEBUG
static void UART2Out(const char* buffer, const uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		// Clock out data
		USART2->TDR = buffer[i];

		// Wait for transfer complete flag
		while (!(USART2->ISR & USART_ISR_TC)); 
	}
}
#endif // DEBUG



// END WITH NEW LINE
