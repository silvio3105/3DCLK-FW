/**
 * @file init.c
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Translation unit with CubeMX configuration.
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
#include 			"init.h"
#include			"main.h"


// ----- FUNCTION DEFINITIONS
/**
  * @brief System Clock Configuration
  * @retval None
  */

void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
	while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
	{
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while(LL_RCC_HSI_IsReady() != 1)
	{

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_LSI_Enable();

	/* Wait till LSI is ready */
	while(LL_RCC_LSI_IsReady() != 1)
	{

	}
	LL_PWR_EnableBkUpAccess();
	if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
	{
		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
	}
	LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
	LL_RCC_LSE_Enable();

	/* Wait till LSE is ready */
	while(LL_RCC_LSE_IsReady() != 1)
	{

	}
	if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
	{
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
	}
	LL_RCC_EnableRTC();
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
	{

	}

	LL_Init1msTick(16000000);

	LL_SetSystemCoreClock(16000000);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_HSI);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
	LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC_Init(void)
{
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
	LL_ADC_InitTypeDef ADC_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	GPIO_InitStruct.Pin = LDR_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LDR_GPIO_Port, &GPIO_InitStruct);


	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_0);

	/** Common config */
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
	LL_ADC_REG_SetSequencerScanDirection(ADC1, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);
	LL_ADC_SetCommonFrequencyMode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_FREQ_MODE_HIGH);
	LL_ADC_DisableIT_EOC(ADC1);
	LL_ADC_DisableIT_EOS(ADC1);
	ADC_InitStruct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV1;
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
	LL_ADC_Init(ADC1, &ADC_InitStruct);

	/* Enable ADC internal voltage regulator */
	LL_ADC_EnableInternalRegulator(ADC1);
	/* Delay for ADC internal voltage regulator stabilization. */
	/* Compute number of CPU cycles to wait for, from delay in us. */
	/* Note: Variable divided by 2 to compensate partially */
	/* CPU processing cycles (depends on compilation optimization). */
	/* Note: If system core clock frequency is below 200kHz, wait time */
	/* is only a few CPU processing cycles. */
	uint32_t wait_loop_index;
	wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
	while(wait_loop_index != 0) wait_loop_index--;

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init(void)
{
	LL_I2C_InitTypeDef I2C_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);


	LL_I2C_EnableAutoEndMode(I2C1);
	LL_I2C_DisableOwnAddress2(I2C1);
	LL_I2C_DisableGeneralCall(I2C1);
	LL_I2C_EnableClockStretching(I2C1);
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
	I2C_InitStruct.Timing = 0x0010061A;
	I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
	I2C_InitStruct.DigitalFilter = 0;
	I2C_InitStruct.OwnAddress1 = 0;
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	LL_I2C_Init(I2C1, &I2C_InitStruct);
	LL_I2C_SetOwnAddress2(I2C1, 0, LL_I2C_OWNADDRESS2_NOMASK);
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
void MX_RTC_Init(void)
{
	LL_RTC_InitTypeDef RTC_InitStruct = {0};

	/* Peripheral clock enable */
	LL_RCC_EnableRTC();

	/** Initialize RTC and set the Time and Date
	 */
	RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
	RTC_InitStruct.AsynchPrescaler = 127;
	RTC_InitStruct.SynchPrescaler = 255;
	LL_RTC_Init(RTC, &RTC_InitStruct);
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)
{
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_5, LL_DMA_REQUEST_8);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_5, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PRIORITY_VERYHIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PDATAALIGN_HALFWORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MDATAALIGN_BYTE);

	TIM_InitStruct.Prescaler = 2 - 1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_InitStruct.Autoreload = 10 - 1;
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_Init(TIM2, &TIM_InitStruct);
	LL_TIM_DisableARRPreload(TIM2);
	LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
	LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);
	TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
	TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
	TIM_OC_InitStruct.CompareValue = 0;
	TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
	LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
	LL_TIM_OC_EnableFast(TIM2, LL_TIM_CHANNEL_CH1);
	LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
	LL_TIM_DisableMasterSlaveMode(TIM2);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	GPIO_InitStruct.Pin = DO_3V3_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
	LL_GPIO_Init(DO_3V3_GPIO_Port, &GPIO_InitStruct);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	GPIO_InitStruct.Pin = BLE_TX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(BLE_TX_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = BLE_RX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(BLE_RX_GPIO_Port, &GPIO_InitStruct);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMA_REQUEST_3);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PRIORITY_MEDIUM);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PDATAALIGN_BYTE);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MDATAALIGN_BYTE);


	USART_InitStruct.BaudRate = BLE_BAUD;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART1);
	LL_USART_Enable(USART1);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void)
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	GPIO_InitStruct.Pin = TX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(TX_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = RX_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(RX_GPIO_Port, &GPIO_InitStruct);

	USART_InitStruct.BaudRate = UART_BAUD;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART2);
	LL_USART_Enable(USART2);
}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
	NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
	LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	/**/
	LL_GPIO_ResetOutputPin(BLE_SYS_GPIO_Port, BLE_SYS_Pin);

	/**/
	LL_GPIO_SetOutputPin(BLE_RST_GPIO_Port, BLE_RST_Pin);

	/**/
	GPIO_InitStruct.Pin = BLE_SYS_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(BLE_SYS_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = BLE_RST_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(BLE_RST_GPIO_Port, &GPIO_InitStruct);

	/**/
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE1);

	/**/
	LL_GPIO_SetPinPull(BLE_LED_GPIO_Port, BLE_LED_Pin, LL_GPIO_PULL_NO);

	/**/
	LL_GPIO_SetPinMode(BLE_LED_GPIO_Port, BLE_LED_Pin, LL_GPIO_MODE_INPUT);

	/**/
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&EXTI_InitStruct);

	/* EXTI interrupt init*/
	NVIC_SetPriority(EXTI0_1_IRQn, 0);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	__disable_irq();

	while (1)
	{

	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

// END WITH NEW LINE
