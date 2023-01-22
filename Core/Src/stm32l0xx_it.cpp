/**
 * @file stm32l0xx_it.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Interrupt handler translation unit.
 * @date 07.01.2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// ----- INCLUDE FILES
#include			"main.h"
#include			"config.h"
#include			"stm32l0xx_it.h"
#include			"LED.h"



/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
	while (1)
	{

	}
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
	while (1)
	{

	}
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{

}


extern volatile uint32_t tick;

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	//tick++;
}

extern volatile uint8_t time;

void RTC_IRQHandler(void)
{
	// Clear EXTI line pending interrupt flag
	EXTI->PR |= EXTI_IMR_IM20;

	// Use check below to make sure interrupt was RTC wake up
	// if (RTC->ISR & RTC_ISR_WUTF)

	// SOON: Just for testing
	time = 1;
}


/**
  * @brief This function handles EXTI line 0 and line 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_1) != RESET)
	{
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
	}
}

/**
  * @brief This function handles DMA1 channel 2 and channel 3 interrupts.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
	
}

/**
  * @brief This function handles DMA1 channel 4, channel 5, channel 6 and channel 7 interrupts.
  */
void DMA1_Channel4_5_6_7_IRQHandler(void)
{
	// Transfer Complete on DMA Channel 5
	// Since only TIM2 CH 0 uses DMA with this IRQ handler, it is not required to do check for interrupt source.
	// if (DMA1->ISR & DMA_ISR_TCIF5)

	// Reset compare value
	TIM2->CCR1 = 0;

	// Stop TIM2 Channel 1
	TIM2->CR1 &= ~TIM_CR1_CEN;	

	// Stop DMA Channel 5
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;	

	// Clear DMA Channel 5 interrupt flag
	DMA1->IFCR |= (DMA_IFCR_CGIF5 | DMA_IFCR_CHTIF5);

	// Stop LED update
	LEDs.stop();
}

// END WITH NEW LINE
