/**
 * @file Clock.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Clock header file.
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

#ifndef _CLOCK_H_
#define _CLOCK_H_

// ----- INCLUDE FILES
#include 			<sRTC.h>


// ----- EXTERNS
extern sRTC sClock;
extern sRTC_time_t rtcTime;
extern const char clockDays[7][4];
extern const char clockAMPM[2][3];


// ----- FUNCTION DECLARATIONS
/**
 * @brief Init RTC.
 * 
 * @return No return value.
 */
void clockInit(void);


/**
 * @brief Get(refresh) RTC time.
 * 
 * @return No return value.
 */
inline void clockGetTime(void)
{
	sClock.get(rtcTime);
}

/**
 * @brief Get day from RTC time.
 * 
 * @return Day from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline uint8_t clockGetDay(void)
{
	return rtcTime.day;
}

/**
 * @brief Get month from RTC time.
 * 
 * @return Month from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline uint8_t clockGetMonth(void)
{
	return rtcTime.month;
}

/**
 * @brief Get real year from RTC.
 * 
 * @return Year from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 * @note Function returns real year - year from RTC + 2000
 */
inline uint16_t clockGetYear(void)
{
	return rtcTime.year + 2000;
}

/**
 * @brief Get weekday index from RTC time.
 * 
 * 1 = Monday
 * 2 = Tuesday
 * 3 = Wednesday
 * 4 = Thursday
 * 5 = Friday
 * 6 = Saturday
 * 7 = Sunday
 * 
 * @return Weekday index from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline sRTC_day_t clockGetWeekDay(void)
{
	return rtcTime.weekDay;
}

/**
 * @brief Get hours from RTC time.
 * 
 * @return Hours from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline uint8_t clockGetHour(void)
{
	return rtcTime.hour;
}

/**
 * @brief Get minutes from RTC time.
 * 
 * @return Minutes from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline uint8_t clockGetMinute(void)
{
	return rtcTime.minute;
}

/**
 * @brief Get seconds from RTC time.
 * 
 * @return Seconds from RTC time.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline uint8_t clockGetSecond(void)
{
	return rtcTime.second;
}

/**
 * @brief Get AM or PM index.
 * 
 * @return \c sRTC_ampm_t::AM if RTC time is AM.
 * @return \c sRTC_ampm_t::PM if RTC time is PM.
 * 
 * @warning Call \ref clockGetTime to refresh RTC time!
 */
inline sRTC_ampm_t clockGetAMPM(void)
{
	return rtcTime.ampm;
}


#endif // _CLOCK_H_

// END WITH NEW LINE
