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


// ----- CODE SNIPPETS
#define CMD_CHECK_ARG_CNTS(_min, _max) \
	if (argCnt < _min || argCnt > _max) { cmdArgCntMinMax(_min, _max); return; }

#define CMD_CHECK_ARG_CNT(_cnt) \
	if (argCnt != _cnt) { cmdArgCnt(_cnt); return; }


// ----- STATIC FUNCTION DECLARATIONS
/**
 * @brief Print to BLE message about invalid argument.
 * 
 * @param arg Number of argument in command.
 * @return No return value.
 */
static void cmdArgNotValid(uint8_t arg);

/**
 * @brief Print to BLE message about number of arguments in command.
 * 
 * @param cnt Number of arguments
 * @return No return value.
 */
static void cmdArgCnt(uint8_t cnt);

/**
 * @brief Print to BLE message with minimum and maximum number of arguments in command. 
 * 
 * @param min Minimum number of arguments.
 * @param max Maximum number of arguments.
 * @return No return value.
 */
static void cmdArgCntMinMax(uint8_t min, uint8_t max);

SCMD_HANDLER(NA);
SCMD_HANDLER(help);
SCMD_HANDLER(reset);
SCMD_HANDLER(blereset);
SCMD_HANDLER(info);
SCMD_HANDLER(set);


// ----- VARIABLES
sCMDList cmdList[] = {
	SCMD_ADD(help, ""),
	SCMD_ADD(reset, "Reset the device"),
	SCMD_ADD(blereset, "Reset BLE module"),
	SCMD_ADD(info, "Get device info"),
	SCMD_ADD(set, "Set time and date. Format: [24H/12H],[H],[M],[S]{,AM/PM},[Day(1-7;1=Mon)],[D],[M],[Y]")
};


// ----- OBJECTS
sCMD<CMD_MAX_ARGS> CMDLine(cmdList, SSTD_ARRAY(cmdList), SCMD_GET(NA), ';', ' ', ',');


// ----- FUNCTION DEFINITIONS


// ----- STATIC FUNCTION DEFINITIONS
static void cmdArgNotValid(uint8_t arg)
{
	BLE.printf("Argument %d is not valid!\n", arg);
}

static void cmdArgCnt(uint8_t cnt)
{
	BLE.printf("Command requires %d arguments!\n", cnt);
}

static void cmdArgCntMinMax(uint8_t min, uint8_t max)
{
	BLE.printf("Command requires between %d and %d arguments!\n", min, max);
}


SCMD_HANDLER(NA)
{
	BLE.printf("Command '%s' does not exist\n", args);
	logf("Command '%s' does not exist\n", args);
}

SCMD_HANDLER(help)
{
	BLE.print("3D Clock commands\nCommand and arguments are case sensitive!\n", 61);

	// Print command descriptions
	for (uint8_t i = 1; i < SSTD_ARRAY(cmdList); i++) BLE.printf("- %s: %s.\n", cmdList[i].cmd, cmdList[i].cmdDescription);
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

SCMD_HANDLER(set)
{
	// Check number of provided arguments
	CMD_CHECK_ARG_CNTS(8, 9);

	// Argument 1
	sRTC_time_format_t timeFormat = sRTC_time_format_t::FORMAT_24H;
	if (sStd::cmp(args[0], "24H")) timeFormat = sRTC_time_format_t::FORMAT_24H;
	else if (sStd::cmp(args[0], "12H")) timeFormat = sRTC_time_format_t::AM_PM;
	else
	{
		cmdArgNotValid(1);
		return;
	}

	// Argument 2
	uint8_t hour = sStd::str2Dec<uint8_t>(args[1]);
	if (sStd::isHour(hour, (uint8_t)timeFormat) != SSTD_OK)
	{
		cmdArgNotValid(2);
		return;
	}

	// Argument 3
	uint8_t minute = sStd::str2Dec<uint8_t>(args[2]);
	if (sStd::isMin(minute) != SSTD_OK)
	{
		cmdArgNotValid(3);
		return;
	}

	// Argument 4
	uint8_t second = sStd::str2Dec<uint8_t>(args[3]);
	if (sStd::isSecond(second) != SSTD_OK)
	{
		cmdArgNotValid(4);
		return;
	}

	// Argument 5 & 6
	uint8_t dayIdx = 1; // Monday
	sRTC_ampm_t ampmTag = sRTC_ampm_t::AM;
	uint8_t offset = 0; // Argument index offset
	if (timeFormat == sRTC_time_format_t::AM_PM)
	{
		// Argument 5 (AM/PM)
		if (sStd::cmp(args[4], "AM")) ampmTag = sRTC_ampm_t::AM;
		else if (sStd::cmp(args[4], "PM")) ampmTag = sRTC_ampm_t::PM;
		else
		{
			cmdArgNotValid(5);
			return;
		}

		// Argument 6 (AM/PM)
		dayIdx = sStd::str2Dec<uint8_t>(args[4]);
		if (dayIdx < 1 || dayIdx > 7)
		{
			cmdArgNotValid(6);
		}

		// Offset argument by 1 after tihs argument
		offset = 1;
	}
	else
	{
		// Argument 5 (24H)
		dayIdx = sStd::str2Dec<uint8_t>(args[4]);
		if (dayIdx < 1 || dayIdx > 7)
		{
			cmdArgNotValid(5);
		}
	}

	// Rest of arguments
	uint8_t day = sStd::str2Dec<uint8_t>(args[5 + offset]);
	uint8_t month = sStd::str2Dec<uint8_t>(args[6 + offset]);
	uint8_t year = sStd::str2Dec<uint16_t>(args[7 + offset]) - 2000;

	if (sStd::validateDate(day, month, 2000 + year) != SSTD_OK)
	{
		BLE.print("Day, month or year is not valid!\n", 34);
		return;
	}

	// Configure time format
	// SOON: Before reinit check time format in config
	sClock.init(timeFormat);

	// Init RTC wakeup timer
	sClock.wakeupEnable(SYS_WAKEUP_CLOCK);

	// Start RTC wakeup timer
	sClock.wakeupStart(SYS_WAKEUP);

	// Set RTC time and date
	if (timeFormat == sRTC_time_format_t::AM_PM) sClock.set(day, month, year, (sRTC_day_t)dayIdx, hour, minute, second);
		else sClock.set(day, month, year, (sRTC_day_t)dayIdx, hour, minute, second, ampmTag);

	// Print message to BLE
	BLE.printf("RTC set to: %s format, %02d:%02d:%02d", args[0], hour, minute, second);
	if (timeFormat == sRTC_time_format_t::AM_PM) BLE.printf(" %s", args[4]);
	BLE.print("\n", 1);
}



// END WITH NEW LINE
