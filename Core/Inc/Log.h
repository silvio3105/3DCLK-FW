/**
 * @file Log.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Header file for log module.
 * @date 08.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _LOG_H_
#define _LOG_H_

// ----- INCLUDE FILES
#include			"main.h"
#include			"sStd.h"


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


// ----- EXTERNS
extern sStd::Logger<LOG_BUFF> Serial;


#endif // _LOG_H_

// END WITH NEW LINE
