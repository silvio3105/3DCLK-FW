/**
 * @file Log.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file for log module.
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


#ifndef _LOG_H_
#define _LOG_H_

// ----- INCLUDE FILES
#include			"main.h"
#include			"sStd.h"
#include			"Clock.h"


// ----- MACROS
// Remove Logger functions if DEBUG is not defined
#ifdef DEBUG
#define log(...) \
	Serial.print(__VA_ARGS__)

#define logf(...) \
	Serial.printf(__VA_ARGS__)
#else
#define log(...) 	
#define logf(...) 
#endif // DEBUG


#ifdef DEBUG
// ----- EXTERNS
extern sStd::Logger<LOG_BUFF> Serial;


// ----- FUNCTION DECLARATIONS
/**
 * @brief Log temperature & relative humidity.
 * 
 * @return No return value.
 * 
 * @warning \c measure method must be called before calling this function!
 */
void logTnH(void);

/**
 * @brief Log RTC time and date.
 * 
 * @return No return value.
 */
inline void logRTC(void)
{
	// SOON: Adjust for 24/AM-PM time format
	logf("Date: %s %02d. %02d. %d.\nTime: %02d:%02d:%02d %s\n", clockDays[clockGetWeekDay() - 1], clockGetDay(), clockGetMonth(), clockGetYear(), clockGetHour(), clockGetMinute(), clockGetSecond(), clockAMPM[clockGetAMPM()]);
}
#endif // DEBUG

#endif // _LOG_H_

// END WITH NEW LINE
