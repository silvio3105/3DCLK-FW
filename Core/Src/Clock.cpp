/**
 * @file Clock.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Clock translation unit.
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
#include			"Clock.h"
#include			"sRTC.h"
#include			"FWConfig.h"
#include			"Log.h"
#include			"LED.h"


// ----- VARIABLES
sRTC_time_t rtcTime;
const char clockDays[7][4] = {
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun"
};

const char clockAMPM[2][3] = {
	"AM",
	"PM"
};


// ----- OBJECTS
sRTC sClock(RTC_HANDLE);


// ----- FUNCTION DEFINITIONS
void clockInit(void)
{
	// Configure RTC
	sClock.init(CFG_TIME_FORMAT);

	// Calibrate RTC
	#ifdef RTC_CALIBRATE
	sClock.calibrate(RTC_CAL_DIR, RTC_CAL_VALUE, RTC_CAL_CYCLE);
	#else
	sClock.calibrate(sRTC_cal_dir_t::RTC_CAL_NEGATIVE, 0, RTC_CAL_CYCLE); // Reset calibration
	#endif // RTC_CALIBRATE

	// Check if RTC time is set
	if (!sClock.isSet()) log("Clock lost\n");		
		else log("Clock OK!\n");	
}


// END WITH NEW LINE
