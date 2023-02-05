/**
 * @file sBLE.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief HM-10/HM-16 library translation unit.
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
#include			"sBLE.h"
#include			<stdarg.h>


// ----- METHOD DEFINITIONS
sBLE_HM::sBLE_HM(TXHandler UARTTX, RXHandler UARTRX, pinHandler sys, pinHandler r, pinStatusHandler st)
{
	TX = UARTTX;
	RX = UARTRX;

	sysKey = sys;
	rst = r;
	status = st;
}

sBLE_HM::~sBLE_HM(void)
{
	TX = nullptr;
	RX = nullptr;

	sysKey = nullptr;
	rst = nullptr;
	status = nullptr;
	rxBuff[0] = '\0';
}

uint8_t sBLE_HM::init(void)
{
	// Return NOK if external handlers are NULL
	if (!(TX && RX && sysKey && rst && status)) return SBLE_NOK;

	// Ping module
	if (ping() == SBLE_OK)
	{
		// Configure status output
		sendCmd("AT+PIO11", 8);
		//TX("AT+PIO11", 8);

		// Return OK status
		return SBLE_OK;
	}

	// Return NOK status
	return SBLE_NOK;
}

void sBLE_HM::disconnect(sBLE_action_t type)
{
	// Software disconnect via command
	if (type == sBLE_action_t::CMD) ping();
		else sysKey(); // Disconnect via GPIO pin
}

void sBLE_HM::reset(sBLE_action_t type)
{
	// Reset via command
	if (type == sBLE_action_t::CMD) send("AT+RESET", 8, nullptr);
		else rst(); // Reset via GPIO pin
}

void sBLE_HM::printf(const char* str, ...)
{
	char buffer[128];

	// Format text string
	va_list args;
	va_start(args, str);	
	uint8_t len = vsnprintf(buffer, sizeof(buffer), str, args);
	va_end(args);

	// Send it
	TX(buffer, len);
}


// ----- PRIVATE METHOD DEFINITIONS
uint8_t sBLE_HM::cmp(const char* input, const char* wanted, const uint8_t len)
{
	// Compare received answer with wanted answer
	for (uint8_t i = 0; i < len; i++)
	{
		// Return NOK status if input is not equal to wanted
		if (input[i] != wanted[i]) return SBLE_NOK;
	}

	return SBLE_OK;
}

uint8_t sBLE_HM::send(const char* tx, uint8_t txLen, const char* rx, const uint8_t rxLen)
{
	// Send command
	TX(tx, txLen);

	// Wait for answer if needed
	if (rx)
	{
		// Receive module answer
		RX(rxBuff, rxLen, '\0');

		// Compare it and return compare status
		return cmp(rxBuff, rx, rxLen);
	}
	else return SBLE_OK;
}

uint8_t sBLE_HM::sendReceive(const char* tx, const uint8_t txLen, const uint8_t rxLen, const char rxStop, char* output, const uint8_t rxOffset, const uint8_t rxMax)
{	
	// Send command
	TX(tx, txLen);

	// Receive answer
	RX(rxBuff, rxLen, rxStop);

	// If first two chars are "OK"
	if (rxBuff[0] == 'O' && rxBuff[1] == 'K' && rxBuff[2] == '+')
	{
		// Copy name to output variable
		memcpy(output, &rxBuff[rxOffset], rxMax);
		
		// Return OK status
		return SBLE_OK;
	}
	else output[0] = '\0';

	// Return NOK status
	return SBLE_NOK;	
}

uint8_t sBLE_HM::sendCmd(const char* cmd, ...)
{
	// Format command string
	va_list args;
	va_start(args, cmd);	
	uint8_t len = vsnprintf(rxBuff, sizeof(rxBuff), cmd, args);
	va_end(args);

	// Send formated command and return status
	return send(rxBuff, len, "OK+", 3);
}


// END WITH NEW LINE
