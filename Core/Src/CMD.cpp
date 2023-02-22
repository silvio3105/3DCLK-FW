/**
 * @file CMD.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Command module translation unit.
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
#include			"CMD.h"
#include			"sCMD.h"
#include			"Log.h"
#include			"sStd.h"
#include			"BLE.h"
#include			"FWConfig.h"
#include			"Clock.h"
#include			"main.h"
#include			<stdlib.h>


// ----- STATIC FUNCTION DECLARATIONS
SCMD_HANDLER(NA);
SCMD_HANDLER(help);
SCMD_HANDLER(reset);
SCMD_HANDLER(blereset);
SCMD_HANDLER(info);
SCMD_HANDLER(settime);
SCMD_HANDLER(setdate);


// ----- VARIABLES
sCMDList cmdList[] = {
	SCMD_ADD(help, ""),
	SCMD_ADD(reset, "Reset the device"),
	SCMD_ADD(blereset, "Reset BLE module"),
	SCMD_ADD(info, "Get device info"),
	SCMD_ADD(settime, "Set clock time. Format: [24H/12H],[H],[M],[S]{,AM/PM}"),
	SCMD_ADD(setdate, "Set clock date. Format: [Day],[D],[M],[Y]")
};


// ----- OBJECTS
sCMD<CMD_MAX_ARGS> CMDLine(cmdList, SSTD_ARRAY(cmdList), SCMD_GET(NA), ';', ' ', ',');


// ----- FUNCTION DEFINITIONS


// ----- STATIC FUNCTION DEFINITIONS
SCMD_HANDLER(NA)
{
	BLE.printf("Command '%s' does not exist\n", args);
	logf("Command '%s' does not exist\n", args);
}

SCMD_HANDLER(help)
{
	BLE.print("3D Clock commands\n", 19);

	// Print command descriptions
	for (uint8_t i = 1; i < SSTD_ARRAY(cmdList); i++)
	{
		BLE.printf("- %s: %s.\n", cmdList[i].cmd, cmdList[i].cmdDescription);
	}
}

SCMD_HANDLER(reset)
{
	BLE.disconnect(sBLE_action_t::PIN);
	delay(100);

	do
	{
		NVIC_SystemReset();
	}
	while (1);
}

SCMD_HANDLER(blereset)
{
	BLE.disconnect(sBLE_action_t::PIN);
	BLE.reset(sBLE_action_t::CMD);
}

SCMD_HANDLER(info)
{
	BLE.print("\n3D Clock info:\n", 17);

	// Print firmware stuff
	BLE.printf("FW: %s\nHW: %s\nBuild: %s\nReset: %d\n", buildInfo.FW, buildInfo.HW, buildInfo.DATE, resetFlags);

	// Print RTC and TnH stuff
	blePrintRTC();
	blePrintTnH();
}

SCMD_HANDLER(settime)
{
	// Check number of provided arguments
	if (argCnt < 4 || argCnt > 5)
	{
		BLE.print("Command requires 4 to 5 arguments.\n", 36);
		return;
	}

	// First argument
	sRTC_time_format_t timeFormat = sRTC_time_format_t::FORMAT_24H;
	if (sStd::cmp(args[0], "24H")) timeFormat = sRTC_time_format_t::FORMAT_24H;
	else if (sStd::cmp(args[0], "12H")) timeFormat = sRTC_time_format_t::AM_PM;
	else
	{
		BLE.print("Time format can be '24H' or '12H'\n", 35);
		return;
	}

	// SOON: Replace with sStd functions
	uint8_t hour = atoi(args[1]);
	uint8_t minute = atoi(args[2]);
	uint8_t second = atoi(args[3]);
}

SCMD_HANDLER(setdate)
{

}


// END WITH NEW LINE
