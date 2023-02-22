/**
 * @file BLE.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Bluetooth module translation unit.
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
#include			"BLE.h"
#include			"main.h"
#include			"Log.h"
#include			"sStd.h"
#include			"TnH.h"
#include			"CMD.h"


// ----- STATIC FUNCTION DECLARATIONS
static void bleTX(const char* str, uint8_t len);
static void bleRX(char* str, uint8_t len, const char stopChar);
static void bleSysKey(void);
static void bleReset(void);
static uint8_t bleStatus(void);


// ----- VARIABLES
volatile uint8_t bleConnAltered = 0; /**< @brief Flag for altered BLE connection. */


// ----- OBJECTS
sBLE_HM BLE(bleTX, bleRX, bleSysKey, bleReset, bleStatus);
sStd::RingBuffer<char, BLE_RX_BUFFER> BLEInput;


// ----- FUNCTION DEFINITIONS
void bleInit(void)
{
	// Ping BLE module
	if (BLE.init() == SBLE_OK)
	{
		// Get BLE module info
		char output[13] = { '\0' };

		// Set BLE init flag
		log("BLE init OK!\n");
		SSTD_BIT_SET(initFlags, INIT_BLE_POS);

		// Print BLE stuff
		BLE.getName(output);
		logf("BLE name: %s\n", output);

		output[0] = '\0';
		BLE.getMac(output);
		logf("BLE MAC: %s\n", output);

		output[6] = '\0';
		BLE.getPIN(output);
		logf("BLE PIN: %s\n", output);

		output[11] = '\0';
		BLE.getVersion(output);
		logf("BLE Version: %s\n", output);
	}
	else log("BLE init NOT OK!\n");
}

void bleConfig(void)
{

}

void blePrintRTC(void)
{
	// Abort if BLE is not connected or RTC is not set
	if (!BLE.isConnected() || !sClock.isSet()) return;

	// SOON: Adjust for 24/AM-PM time format
	BLE.printf("Date: %s %02d. %02d. %d.\nTime: %02d:%02d:%02d %s\n", clockDays[clockGetWeekDay() - 1], clockGetDay(), clockGetMonth(), clockGetYear(), clockGetHour(), clockGetMinute(), clockGetSecond(), clockAMPM[clockGetAMPM()]);
}

void blePrintTnH(void)
{
	// Abort if BLE is not connected
	if (!BLE.isConnected()) return;

	int8_t tnh = 0;

	// Print RH if is it calculated
	uint8_t ret = TnH.rh((uint8_t&)tnh);
	if (ret == SHT40_OK || ret == SHT40_OLD_DATA) BLE.printf("Relative Humidity: %d%%\n", tnh);

	// Print temperature if is it calculated
	ret = TnH.temperature(tnh);
	if (ret == SHT40_OK || ret == SHT40_OLD_DATA) BLE.printf("Temperature: %d°C\n", tnh); // SOON: Adjust for °F	
}

void bleGetChar(void)
{
	// Clear override error if needed
	if (BLE_UART->ISR & USART_ISR_ORE)
	{
		BLE_UART->ICR |= USART_ICR_ORECF;
		(void)BLE_UART->RDR;
	}

	// If new byte is received
	if (BLE_UART->ISR & USART_ISR_RXNE)
	{
		// Store received char
		char tmpChar = BLE_UART->RDR;

		// If string end is received
		if (tmpChar == '\r')
		{
			// Replace \r or \n with \0 char
			BLEInput.write('\0');

			// Pass whole string to command handler

			// SOON: Echo test
			char tmpBuff[BLE_RX_BUFFER];
			BLEInput.read(tmpBuff, BLEInput.used());
			logf("echo: '%s'\n", tmpBuff);
			CMDLine.exe(tmpBuff);
		}
		else if (tmpChar != '\n') BLEInput.write(tmpChar);
	}	
}


// ----- STATIC FUNCTION DEFINITIONS
static void bleTX(const char* str, uint8_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		// Wait for transfer complete flag
		while (!(BLE_UART->ISR & USART_ISR_TC)); 

		// Clock out data
		BLE_UART->TDR = str[i];
	}
}

static void bleRX(char* str, uint8_t len, const char stopChar)
{
	uint8_t idx = 0;

	
	(void)BLE_UART->RDR;

	// While not all bytes are received
	do
	{
		// Clear override error
		BLE_UART->ICR |= USART_ICR_ORECF;

		// If new byte is received
		if (BLE_UART->ISR & USART_ISR_RXNE)
		{
			// Copy received byte into buffer
			str[idx] = BLE_UART->RDR;

			// Break if stop char is received
			if (str[idx] == stopChar) break;

			// Increase index
			idx++;
		}
	}
	while (idx != len);
}

static void bleSysKey(void)
{
	LL_GPIO_WriteOutputPort(BLE_SYS_GPIO_Port, LL_GPIO_ReadOutputPort(BLE_SYS_GPIO_Port) | BLE_SYS_Pin);
	delay(SBLE_HM_DISCONNECT_TIME);
	LL_GPIO_ResetOutputPin(BLE_SYS_GPIO_Port, LL_GPIO_ReadOutputPort(BLE_SYS_GPIO_Port) | BLE_SYS_Pin);
}

static void bleReset(void)
{
	LL_GPIO_ResetOutputPin(BLE_RST_GPIO_Port, LL_GPIO_ReadOutputPort(BLE_RST_GPIO_Port) | BLE_RST_Pin);
	delay(SBLE_HM_RESET_TIME);
	LL_GPIO_WriteOutputPort(BLE_RST_GPIO_Port, LL_GPIO_ReadOutputPort(BLE_RST_GPIO_Port) | BLE_RST_Pin);
}

static uint8_t bleStatus(void)
{
	if (LL_GPIO_ReadInputPort(BLE_LED_GPIO_Port) & BLE_LED_Pin) return SBLE_OK;
	
	return SBLE_NOK;
}


// END WITH NEW LINE