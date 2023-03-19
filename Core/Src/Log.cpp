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
#include			"TnH.h"


#ifdef DEBUG
#if LOG_METHOD == 0 // Sys UART
// ----- FUNCTION DECLARATIONS
/**
 * @brief Handler for transmitting characters over RTT.
 * 
 * @param buffer Pointer to C-string to transmit.
 * @param len Length of \c buffer
 * @return No return value.
 */
static void uartTX(const char* buffer, const uint16_t len);

#elif LOG_METHOD == 1 // Sys RTT

/**
 * @brief Handler for printing over RTT.
 * 
 * @param buffer Pointer to C-string to print.
 * @param len Length of \c buffer
 * @return No return value.
 */
static void rttTX(const char* buffer, const uint16_t len);
#endif // LOG_METHOD


// ----- OBJECTS
#if LOG_METHOD == 0 // If Sys UART is used
/**
 * @brief Logger object.
 * 
 * \c LOG_BUFF Buffer size.
 * \c uartTX Function for handling \ref SYS_UART transmits.
 */
sStd::Logger<LOG_BUFF> Serial(uartTX);

#elif LOG_METHOD == 1 // If Sys RTT is used
/**
 * @brief Logger object.
 * 
 * \c LOG_BUFF Buffer size.
 * \c rttTX Function for handling RTT prints.
 */
sStd::Logger<LOG_BUFF> Serial(rttTX);

/**
 * @brief RTT object.
 * 
 * \c LOG_BUFF size of RTT's buffer for printf method.
 * \c LOG_RTT_CH RTT channel.
 */
sRTT<LOG_BUFF> SysRTT(LOG_RTT_CH);

#endif // LOG_METHOD

#endif // DEBUG


// ----- FUNCTION DEFINITIONS
void logRTC(void)
{
	#ifdef DEBUG
	// Abort if RTC is not set
	if (!sClock.isSet()) return;

	// SOON: Adjust for 24/AM-PM time format
	logf("Date: %s %02d. %02d. %d.\nTime: %02d:%02d:%02d %s\n", clockDays[clockGetWeekDay() - 1], clockGetDay(), clockGetMonth(), clockGetYear(), clockGetHour(), clockGetMinute(), clockGetSecond(), clockAMPM[clockGetAMPM()]);
	#endif // DEBUG
}

void logTnH(void)
{
	#ifdef DEBUG
	int8_t tnh = 0;

	// Print temperature if calculated succesfully
	uint8_t ret = TnH.temperature(tnh);
	if (ret == SHT40_OK || ret == SHT40_OLD_DATA) logf("Temperature: %d°C\n", tnh); // SOON: Add temp units

	// Print relative humidity if calculated succesfully
	ret = TnH.rh((uint8_t&)tnh);
	if (ret == SHT40_OK || ret == SHT40_OLD_DATA) logf("Humidity: %d%%\n", tnh);
	#endif // DEBUG
}


// ----- STATIC FUNCTION DEFINITIONS
#ifdef DEBUG
#if LOG_METHOD == 0
static void uartTX(const char* buffer, const uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		// Wait for transfer complete flag
		while (!(SYS_UART->ISR & USART_ISR_TC)); 

		// Clock out data
		SYS_UART->TDR = buffer[i];
	}
}

#elif LOG_METHOD == 1

static void rttTX(const char* buffer, const uint16_t len)
{
	// Print over RTT
	SysRTT.print(buffer, len);
}
#endif // LOG_METHOD

#endif // DEBUG


// END WITH NEW LINE
