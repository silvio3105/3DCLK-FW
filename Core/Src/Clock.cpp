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
#include			<Clock.h>
#include			<sRTC.h>
#include			<config.h>
#include			<Log.h>


// ----- OBJECTS
sRTC sClock(RTC);


// ----- FUNCTION DEFINITIONS
void clockInit(void)
{
	// For test
	sRTC_time_t time = {
		sRTC_day_t::THURSDAY,
		11,
		9,
		18,

		11,
		59,
		50,
	};	

	sClock.init(CLOCK_DEF_FORMAT);

	if (!sClock.isSet())
	{
		log("Clock lost, reinit...\n");
		sClock.set(time);
		log("Clock set!\n");
	}
	else log("Clock OK!\n");	
}


// END WITH NEW LINE
