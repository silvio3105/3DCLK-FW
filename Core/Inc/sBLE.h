/**
 * @file sBLE.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief HM-10/HM-16 library header file.
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


#ifndef _SBLE_H_
#define _SBLE_H_


/** \addtogroup sBLE
 * @{
 * Frameworkless simple BLE library for various BLE modules.
*/


// ----- INCLUDE FILES
#include			<stdint.h>
#include			<string.h>
#include			<stdio.h>

// ----- DEFINES
// RETURN CODES
#define SBLE_NOK						0 /**< @brief Not OK status return code. */
#define SBLE_OK							1 /**< @brief OK status return code. */

// HM-10/HM-16 DATASHEET STUFF
#define SBLE_HM_DISCONNECT_TIME			100 /**< @brief Minimum time between toggling system key pin for breaking connection. */
#define SBLE_HM_RESET_TIME				100 /**< @brief Minimum time between toggling reset pin. */


// ----- ENUMS
/**
 * @brief BLE module pin or command actions.
 * 
 */
enum sBLE_action_t : uint8_t {
	CMD = 0, /**< @brief Execute action with command. */
	PIN = 1 /**< @brief Execute action with GPIO pin. */
};

/**
 * @brief BLE roles.
 * 
 */
enum sBLE_role_t : char {
	PERIPHERAL = '0', /**< @brief Peripheral role. */
	CENTRAL = '1' /**< @brief Central role. */
};

/**
 * @brief BLE UART baud rates.
 * 
 */
enum sBLE_baud_t : char {
	BAUD_1200BPS = '0', /**< @brief UART baud 1200bps. */
	BAUD_2400BPS = '1', /**< @brief UART baud 2400bps. */
	BAUD_4800BPS = '2', /**< @brief UART baud 4800bps. */
	BAUD_9600BPS = '3', /**< @brief UART baud 9600bps. */
	BAUD_19200BPS = '4', /**< @brief UART baud 19200bps. */
	BAUD_38400BPS = '5', /**< @brief UART baud 38400bps. */
	BAUD_57600BPS = '6', /**< @brief UART baud 57600bps. */
	BAUD_115200BPS = '7', /**< @brief UART baud 115200bps. */
	BAUD_230400BPS = '8' /**< @brief UART baud 230400bps. */
};

/**
 * @brief BLE start type.
 * 
 */
enum sBLE_start_t : char {
	START_AUTO = '0', /**< @brief Auto start after power-up or reset. */
	START_MANUAL = '1' /**< @brief Manual start. */
};

/**
 * @brief BLE notify connections.
 * 
 */
enum sBLE_notify_t : char {
	NOTI_DISABLE = '0', /**< @brief Disable connection notification. */
	NOTI_ENABLE = '1' /**< @brief Enable connection notification. */
};

/**
 * @brief BLE sleep types.
 * 
 */
enum sBLE_sleep_t : char {
	SLEEP_AUTO = '0', /**< @brief Automatic sleep. */
	SLEEP_MANUAL = '1' /**< @brief Manual sleep. */
};



/**
 * @brief HM-10/HM-16 advertising intervals.
 * 
 */
enum sBLE_HM_adv_interval_t : char {
	ADV_100MS = '0', /**< @brief HM-10/HM-16 advertising interval of 100ms. */
	ADV_152_5MS = '1', /**< @brief HM-10/HM-16 advertising interval of 152.52ms. */
	ADV_211_25MS = '2', /**< @brief HM-10/HM-16 advertising interval of 211.25ms. */
	ADV_318_75MS = '3', /**< @brief HM-10/HM-16 advertising interval of 318.75ms. */
	ADV_417_5MS = '4', /**< @brief HM-10/HM-16 advertising interval of 417.5ms. */
	ADV_546_25MS = '5', /**< @brief HM-10/HM-16 advertising interval of 546.25ms. */
	ADV_760MS = '6', /**< @brief HM-10/HM-16 advertising interval of 760ms. */
	ADV_852_5MS = '7', /**< @brief HM-10/HM-16 advertising interval of 852.5ms. */
	ADV_1022_5MS = '8', /**< @brief HM-10/HM-16 advertising interval of 1022.5ms. */
	ADV_1285MS = '9', /**< @brief HM-10/HM-16 advertising interval of 1285ms. */
	ADV_2S = 'A', /**< @brief HM-10/HM-16 advertising interval of 2s. */
	ADV_3S = 'B', /**< @brief HM-10/HM-16 advertising interval of 3s. */
	ADV_4S = 'C', /**< @brief HM-10/HM-16 advertising interval of 4s. */
	ADV_5S = 'D', /**< @brief HM-10/HM-16 advertising interval of 5s. */
	ADV_6S = 'E', /**< @brief HM-10/HM-16 advertising interval of 6s. */
	ADV_7S = 'F' /**< @brief HM-10/HM-16 advertising interval of 7s. */
};

/**
 * @brief HM-10/HM-16 gain powers.
 * 
 */
enum sBLE_HM_power_t : char {
	GAIN_n18DBM = '0', /**< @brief HM-10/HM-16 -18dBm gain. */
	GAIN_n12DBM = '1', /**< @brief HM-10/HM-16 -12dBm gain. */
	GAIN_n6DBM = '2', /**< @brief HM-10/HM-16 -6dBm gain. */
	GAIN_n3DBM = '3', /**< @brief HM-10/HM-16 -3dBm gain. */
	GAIN_n2DBM = '4', /**< @brief HM-10/HM-16 -2dBm gain. */
	GAIN_n1 = '5', /**< @brief HM-10/HM-16 -1dBm gain. */
	GAIN_0DBM = '6', /**< @brief HM-10/HM-16 0dBm gain. */
	GAIN_3DBM = '7' /**< @brief HM-10/HM-16 3dBm gain. */
};

/**
 * @brief HM-10/HM-16 advertise modes.
 * 
 */
enum sBLE_HM_adv_mode_t : char {
	NORMAL = '0', /**< @brief HM-10/HM-16 normal advertise mode. */
	RELIABLE = '1' /**< @brief HM-10/HM-16 reliable advertise mode. */
};

/**
 * @brief HM-10/HM-16 authentication methods.
 * 
 */
enum sBLE_HM_auth_t : char {
	NO_PIN = '0', /**< @brief No PIN is needed. */
	AUTH_NO_PIN = '1', /**< @brief Auth without PIN. */
	AUTH_PIN = '2', /**< @brief Auth with PIN. */
	AUTH_BOND = '3' /**< @brief Auth with PIN and bond. */
};

/**
 * @brief HM-10/HM-16 advertising methods.
 * 
 */
enum sBLE_HM_adv_type_t : char {
	ADV_SR_CONN = '0', /**< @brief Advertising, scan response, connectable. */
	ONLY_LAST_DEV = '1', /**< @brief Allow last device to connect in 1.27s. */
	ONLY_ADV_SR = '2', /**< @brief Advertising and scan response. */
	ONLY_ADV = '3' /**< @brief Only advertising. */
};

/**
 * @brief HM-10/HM-16 TX gains.
 * 
 */
enum sBLE_HM_gain_tx_t : char {
	NO_TX_GAIN = '0', /**< @brief No TX gain. */
	HIGH_GAIN = '1' /**< @brief High TX gain. */
};

/**
 * @brief HM-10/HM-16 RX gains.
 * 
 */
enum sBLE_HM_gain_rx_t : char {
	NO_RX_GAIN = '0', /**< @brief No RX gain. */
	OPEN_GAIN = '1' /**< @brief Open RX gain. */
};

/**
 * @brief HM-10/HM-16 module work types.
 * 
 */
enum sBLE_HM_mode_t : char {
	TX_MODE = '0', /**< @brief Transmission mode only. */
	LIMITED_N_TX_MODE = '1', /**< @brief Transmission mode with remote AT commands. */
	REMOTE_N_TX_MODE = '2' /**< @brief Transmission mode with limited AT commands. */
};


// ----- TYPEDEFS
/**
 * @brief UART TX handler.
 * 
 * @param str Pointer to string buffer for TX.
 * @param len Length of \c str
 * @return No return value.
 */
typedef void (*TXHandler)(const char* str, uint8_t len);

/**
 * @brief UART RX handler.
 * 
 * @param str Pointer to RX buffer.
 * @param len Number of bytes to receive.
 * @param stopChar Stop character.
 * @return No return value.
 */
typedef void (*RXHandler)(char* str, uint8_t len, const char stopChar);

/**
 * @brief GPIO write pin handler.
 * 
 * @return No return value.
 */
typedef void (*pinHandler)(void);

/**
 * @brief GPIO read pin handler.
 * 
 * @return \c SBLE_NOK if GPIO pin is low.
 * @return \c SBLE_OK if GPIO pin is high.
 */
typedef uint8_t (*pinStatusHandler)(void);


// ----- CLASSES
/**
 * @brief HM-10/HM-16 class.
 * 
 * @warning Maximum RX is 24 bytes.
 */
class sBLE_HM
{
	// PUBLIC STUFF
	public:
	// OBJECT CONSTRUCTORS AND DECONSTRUCTORS
	/**
	 * @brief HM-10/HM-16 object constructor.
	 * 
	 * @param UARTTX Pointer to external UART TX handler.
	 * @param UARTRX Pointer to external UART RX handler.
	 * @param sys Pointer to external handler for controlling system key pin.
	 * @param r Pointer to external handler for controlling reset pin.
	 * @param st Pointer to external handler for reading status pin.
	 * @return No return value.
	 */
	sBLE_HM(TXHandler UARTTX, RXHandler UARTRX, pinHandler sys, pinHandler r, pinStatusHandler st);

	/**
	 * @brief HM-10/HM-16 object deconstructor.
	 * 
	 * @return No return value.
	 */
	~sBLE_HM(void);

	// METHOD DECLARATIONS
	/**
	 * @brief Init HM-10/HM-16 BLE module.
	 * 
	 * Function checks external handlers, pings BLE module and configures status pin.
	 * 
	 * @return \c SBLE_NOK if handlers are not provided or module ping is not successful.
	 * @return \c SBLE_OK if handlers are provided and module ping is successful.
	 */
	uint8_t init(void);

	/**
	 * @brief Break bluetooth connection.
	 * 
	 * @param type Break connection using command or using GPIO pin.
	 * @return No return value.
	 */
	void disconnect(sBLE_action_t type);

	/**
	 * @brief Reset bluetooth module.
	 * 
	 * @param type Reset using command or using GPIO pin.
	 * @return No return value.
	 */
	void reset(sBLE_action_t type);

	/**
	 * @brief Ping HM-10/HM-16 module.
	 * 
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t ping(void)
	{
		return send("AT", 2, "OK", 2);
	}

	/**
	 * @brief Is BLE module has connection.
	 * 
	 * @return \c SBLE_NOK BLE module has no connection.
	 * @return \c SBLE_OK BLE module has connection.
	 */
	inline uint8_t isConnected(void)
	{
		return status();
	}

	/**
	 * @brief Renew HM-10/HM-16 module.
	 * 
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t renew(void)
	{
		return send("AT+RENEW", 8, "OK", 2);
	}

	/**
	 * @brief Get HM-10/HM-16 MAC address.
	 * 
	 * @param output Pointer to output for MAC address.
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getMac(char* output)
	{
		return sendReceive("AT+ADDR?\r\n", 10, 19, '\r', output, 7, 12);
	}

	/**
	 * @brief Set HM-10/HM-16 name.
	 * 
	 * @param input Pointer to new BLE name.
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setName(const char* input)
	{
		return sendCmd("AT+NAME%s", input);
	}

	/**
	 * @brief Get HM-10/HM-16 name.
	 * 
	 * Array for \c output must be 13 bytes.
	 * 
	 * @param output Pointer to output C-string array.
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getName(char* output)
	{
		// Answer will be: "OK+Get:Name\r\n" where maximum name length is 13 chars.
		return sendReceive("AT+NAME?\r\n", 10, 21, '\r', output, 7, 13);
	}

	/**
	 * @brief Set advertising interval.
	 * 
	 * @param interval Advertising interval. See \ref sBLE_HM_adv_interval_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setAdvInterval(sBLE_HM_adv_interval_t interval)
	{
		return sendCmd("AT+ADVI%c", interval);
	}

	/**
	 * @brief Get advertising interval.
	 * 
	 * @param interval Pointer to output variable. See \ref sBLE_HM_adv_interval_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getAdvInterval(sBLE_HM_adv_interval_t* interval)
	{
		return sendReceive("AT+ADVI?\r\n", 10, 9, '\r', (char*)interval, 7, 1);
	}

	/**
	 * @brief Set advertise type.
	 * 
	 * @param type Advertise type. See \ref sBLE_HM_adv_type_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setAdvType(sBLE_HM_adv_type_t type)
	{
		return sendCmd("AT+ADTY%c", type);
	}

	/**
	 * @brief Get advertise type.
	 * 
	 * @param type Pointer to output variable. See \ref sBLE_HM_adv_type_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getAdvType(sBLE_HM_adv_type_t* type)
	{
		return sendReceive("AT+ADTY?\r\n", 10, 9, '\r', (char*)type, 7, 1);
	}

	/**
	 * @brief Set UART baud rate.
	 * 
	 * @param baud UART baud rate. See \ref sBLE_baud_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setBaud(sBLE_baud_t baud)
	{
		return sendCmd("AT+BAUD%c", baud);
	}

	/**
	 * @brief Set TX gain.
	 * 
	 * @param gain TX gain. See \ref sBLE_HM_gain_tx_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setTXGain(sBLE_HM_gain_tx_t gain)
	{
		return sendCmd("AT+GAIT%c", gain);
	}

	/**
	 * @brief Get TX gain.
	 * 
	 * @param gain Pointer to output variable. See \ref sBLE_HM_gain_tx_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getTXGain(sBLE_HM_gain_tx_t* gain)
	{
		return sendReceive("AT+GAIT?\r\n", 10, 9, '\r', (char*)gain, 7, 1);
	}

	/**
	 * @brief Set RX gain.
	 * 
	 * @param gain RX gain. See \ref sBLE_HM_gain_rx_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setRXGain(sBLE_HM_gain_rx_t gain)
	{
		return sendCmd("AT+GAIN%c", gain);
	}

	/**
	 * @brief Get RX gain.
	 * 
	 * @param gain Pointer to output variable. See \ref sBLE_HM_gain_rx_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getRXGain(sBLE_HM_gain_rx_t* gain)
	{
		return sendReceive("AT+GAIN?\r\n", 10, 9, '\r', (char*)gain, 7, 1);
	}

	/**
	 * @brief Set module work type.
	 * 
	 * @param type Module work type. See \ref sBLE_start_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setWorkType(sBLE_start_t type)
	{
		return sendCmd("AT+IMME%c", type);
	}

	/**
	 * @brief Get module work type.
	 * 
	 * @param type Pointer to output variable. See \ref sBLE_start_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getWorkType(sBLE_start_t* type)
	{
		return sendReceive("AT+IMME?\r\n", 10, 9, '\r', (char*)type, 7, 1);
	}

	/**
	 * @brief Set HM-10/HM-16 mode.
	 * 
	 * @param mode Module mode. See \ref sBLE_HM_mode_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setMode(sBLE_HM_mode_t mode)
	{
		return sendCmd("AT+MODE%c", mode);
	}

	/**
	 * @brief Get HM-10/HM-16 mode.
	 * 
	 * @param mode Pointer to output variable. See \ref sBLE_HM_mode_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getMode(sBLE_HM_mode_t* mode)
	{
		return sendReceive("AT+MODE?\r\n", 10, 9, '\r', (char*)mode, 7, 1);
	}

	/**
	 * @brief Set connection notify.
	 * 
	 * @param type Connection notify. See \ref sBLE_notify_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setConnNotify(sBLE_notify_t type)
	{
		return sendCmd("AT+NOTI%c", type);
	}

	/**
	 * @brief Get connection notify.
	 * 
	 * @param type Pointer to output variable. See \ref sBLE_notify_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getConnNotify(sBLE_notify_t* type)
	{
		return sendReceive("AT+NOTI?\r\n", 10, 9, '\r', (char*)type, 7, 1);
	}

	/**
	 * @brief Set BLE PIN.
	 * 
	 * @param pin BLE PIN. Must be 6 chars. Only numbers.
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t setPIN(const char* pin)
	{
		return sendCmd("AT+PASS%s", pin);
	}

	/**
	 * @brief Get BLE PIN.
	 * 
	 * @param pin Pointer to output variable. Must be array 6 chars long.
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed.
	 */
	inline uint8_t getPIN(char* pin)
	{
		return sendReceive("AT+PASS?\r\n", 10, 14, '\r', pin, 7, 6);
	}

	/**
	 * @brief Set sleep mode.
	 * 
	 * @param mode Sleep mode. See \ref sBLE_sleep_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t setSleepMode(sBLE_sleep_t mode)
	{
		return sendCmd("AT+PWRM%c", mode);
	}

	/**
	 * @brief Get sleep mode.
	 * 
	 * @param mode Pointer to output variable. See \ref sBLE_sleep_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t getSleepMode(sBLE_sleep_t* mode)
	{
		return sendReceive("AT+PWRM?\r\n", 10, 9, '\r', (char*)mode, 7, 1);
	}

	/**
	 * @brief Set HM-10/HM-16 output power.
	 * 
	 * @param power Output power. See \ref sBLE_HM_power_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t setPower(sBLE_HM_power_t power)
	{
		return sendCmd("AT+POWE%c", power);
	}

	/**
	 * @brief Get HM-10/HM-16 output power.
	 * 
	 * @param power Pointer to output variable. See \ref sBLE_HM_power_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t getPower(sBLE_HM_power_t* power)
	{
		return sendReceive("AT+POWE?\r\n", 10, 9, '\r', (char*)power, 7, 1);
	}

	/**
	 * @brief Set HM-10/HM-16 advertise mode.
	 * 
	 * @param mode Advertise mode. See \ref sBLE_HM_adv_mode_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t setAdvMode(sBLE_HM_adv_mode_t mode)
	{
		return sendCmd("AT+RELI%c", mode);
	}

	/**
	 * @brief Get HM-10/HM-16 advertise mode.
	 * 
	 * @param mode Pointer to output variable. See \ref sBLE_HM_adv_mode_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t getAdvMode(sBLE_HM_adv_mode_t* mode)
	{
		return sendReceive("AT+RELI?\r\n", 10, 9, '\r', (char*)mode, 7, 1);
	}

	/**
	 * @brief Set BLE role.
	 * 
	 * @param role BLE role. See \ref sBLE_role_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t setRole(sBLE_role_t role)
	{
		return sendCmd("AT+ROLE%c", role);
	}

	/**
	 * @brief Get BLE role.
	 * 
	 * @param role Pointer to output variable. See \ref sBLE_role_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t getRole(sBLE_role_t* role)
	{
		return sendReceive("AT+ROLE?\r\n", 10, 9, '\r', (char*)role, 7, 1);
	}

	/**
	 * @brief Enter into sleep mode.
	 * 
	 * @return No return value.
	 */
	inline void sleep(void)
	{
		send("AT+SLEEP", 8, "OK", 2);
	}

	/**
	 * @brief Start BLE.
	 * 
	 * @return No return value.
	 */
	inline void start(void)
	{
		send("AT+START", 8, "OK", 2);
	}

	/**
	 * @brief Set auth mode.
	 * 
	 * @param mode Auth mode. See \ref sBLE_HM_auth_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t setAuthMode(sBLE_HM_auth_t mode)
	{
		return sendCmd("AT+TYPE%c", mode);
	}

	/**
	 * @brief Get auth mode.
	 * 
	 * @param mode Pointer to output variable. See \ref sBLE_HM_auth_t
	 * @return \c SBLE_NOK if command is not succesfully executed.
	 * @return \c SBLE_OK if command is succesfully executed. 
	 */
	inline uint8_t getAuthMode(sBLE_HM_auth_t* mode)
	{
		return sendReceive("AT+TYPE?\r\n", 10, 9, '\r', (char*)mode, 7, 1);
	}


	// PRIVATE STUFF
	private:
	// VARIABLES
	TXHandler TX = nullptr; /**< @brief Pointer to UART TX handler. */
	RXHandler RX = nullptr; /**< @brief Pointer to UART RX handler. */
	pinHandler sysKey = nullptr; /**< @brief Pointer to system key GPIO handler. */
	pinHandler rst = nullptr; /**< @brief Pointer to reset GPIO handler. */
	pinStatusHandler status = nullptr; /**< @brief Pointer to status GPIO handler. */
	char rxBuff[24] = { '\0' }; /**< @brief UART RX buffer. */

	// METHOD DECLARATIONS
	/**
	 * @brief Compare received answer with wanted answer.
	 * 
	 * @param input Pointer to received answer.
	 * @param wanted Pointer to wanted answer. 
	 * @param len Length of both \c input and \c wanted inputs.
	 * @return \c SBLE_NOK if \c input and \c wanted is not equal.
	 * @return \c SBLE_OK if \c input and \c wanted is equal.
	 */
	uint8_t cmp(const char* input, const char* wanted, const uint8_t len);

	/**
	 * @brief Send command to BLE module and wait for OK answer.
	 * 
	 * @param tx Pointer to command to send.
	 * @param txLen Length of \c tx
	 * @param rx Pointer to wanted answer.
	 * @param rxLen Length of wanted answer in \c rx Not needed if \c rx = \c nullptr
	 * @return \c SBLE_NOK if received answer is not equal to \c rx
	 * @return \c SBLE_OK if received answer is equal to \c rx
	 */
	uint8_t send(const char* tx, uint8_t txLen, const char* rx, const uint8_t rxLen = 0);

	/**
	 * @brief Send command to BLE module and get answer.
	 * 
	 * @param tx Pointer to command to send.
	 * @param txLen Length of \c tx
	 * @param rxLen Number of bytes to receive.
	 * @param rxStop Stop character.
	 * @param output Pointer to output variable.
	 * @param rxOffset Index of first character in received answer.
	 * @param rxMax Length of wanted answer.
	 * @return \c SBLE_NOK if \c OK is not received.
	 * @return \c SBLE_OK if \c OK is received.
	 */
	uint8_t sendReceive(const char* tx, const uint8_t txLen, const uint8_t rxLen, const char rxStop, char* output, const uint8_t rxOffset, const uint8_t rxMax);

	/**
	 * @brief Format and send command to BLE module.
	 * 
	 * @param cmd Pointer to command C-string.
	 * @param ... Command arguments.
	 * @return \c SBLE_NOK if received answer is not equal to \c rx
	 * @return \c SBLE_OK if received answer is equal to \c rx 
	 */
	uint8_t sendCmd(const char* cmd, ...);
};

#endif // _SBLE_H_

// END WITH NEW LINE
