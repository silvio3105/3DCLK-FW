/**
 * @file TnH.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Translation unit for temperature & humidity sensor module.
 * @date 08.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// ----- INCLUDE FILES
#include			"TnH.h"
#include			"sStd.h"
#include			"Log.h"


// ----- FUNCTION DECLARATIONS
static void I2C1read(uint8_t addr, uint8_t* data, uint8_t len, uint16_t d);
static void I2C1write(uint8_t addr, uint8_t* data, uint8_t len, uint16_t d);


// ----- OBJECTS
#if (TNH_SENSOR == SHT40_AD) || (TNH_SENSOR == SHT40_B)
SHT40 TnH = SHT40(TNH_SENS_ADDR, I2C1read, I2C1write);
#endif // TNH_SENSOR


// ----- EXTERNS
extern uint8_t initFlags;


// ----- FUNCTION DEFINITIONS
void I2C1read(uint8_t addr, uint8_t* data, uint8_t len, uint16_t d)
{
	// Slave address
	I2C1->CR2 |= (addr << 1);

	// Read Request
	I2C1->CR2 |= I2C_CR2_RD_WRN;

	// Number of bytes
	I2C1->CR2 |= (len << 16);

	// Start I2C
	I2C1->CR2 |= I2C_CR2_START;	

	// Clock out data
	for (uint8_t i = 0; i < len; i++)
	{
		while (!(I2C1->ISR & I2C_ISR_RXNE));
		data[i] = I2C1->RXDR;
	}

	// Generate STOP
	I2C1->CR2 |= I2C_CR2_STOP;

	// Wait for STOP
	while (!(I2C1->ISR & I2C_ISR_STOPF));

	// Clear STOP
	I2C1->ICR &= ~I2C_ICR_STOPCF;

	// Reset CR2 register
	I2C1->CR2 = 0x0;

	// Add delay if needed
	if (d) delay(d);
}

void I2C1write(uint8_t addr, uint8_t* data, uint8_t len, uint16_t d)
{
	// Wait if I2C is busy
	while (I2C1->ISR & I2C_ISR_BUSY);

	// Slave address
	I2C1->CR2 |= (addr << 1);

	// Write Request
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;

	// Number of bytes
	I2C1->CR2 |= (len << 16);

	// Generate START
	I2C1->CR2 |= I2C_CR2_START;

	// Clock out data
	for (uint8_t i = 0; i < len; i++)
	{
		// Wait for empty TXDR register
		while (!(I2C1->ISR & I2C_ISR_TXIS));

		// Write data
		I2C1->TXDR = data[i];		
	}

	// Generate STOP
	I2C1->CR2 |= I2C_CR2_STOP;

	// Wait for STOP
	while (!(I2C1->ISR & I2C_ISR_STOPF));

	// Clear STOP
	I2C1->ICR &= ~I2C_ICR_STOPCF;

	// Reset CR2 register
	I2C1->CR2 = 0x0;

	// Add delay if needed
	if (d) delay(d);
}

void tnhInit(void)
{
	SSTD_BIT_CLEAR(initFlags, INIT_TNH_POS);
	switch (TnH.init(TNH_TEMP_UNIT))
	{
		case SHT40_OK:
		{
			log("TnH init OK\n");
			logf("TnH S/N: %d\n", TnH.whoAmI());

			// Set init flag for TnH
			SSTD_BIT_SET(initFlags, INIT_TNH_POS);
			break;
		}

		case SHT40_NOK:
		{
			log("TnH init NOT OK\n");
			break;
		}

		case SHT40_I2CH_R:
		case SHT40_I2CH_W:
		{
			log("TnH handlers NULL\n");
			break;
		}

		default:
		{
			log("TnH init N/A\n");
			break;
		}
	}	
}


// END WITH NEW LINE
