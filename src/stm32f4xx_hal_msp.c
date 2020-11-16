/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp_template.c
  * @author  MCD Application Team
  * @brief   This file contains the HAL System and Peripheral (PPP) MSP initialization
  *          and de-initialization functions.
  *          It should be copied to the application folder and renamed into 'stm32f4xx_hal_msp.c'.           
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/**
  * @brief  Initializes the Global MSP.
  * @note   This function is called from HAL_Init() function to perform system
  *         level initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */
void HAL_MspInit(void)
{
	// Set Priority Grouping.
	// 4 Bits of Preempt Priority, 0 Bits for Subpriority.
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// Set Priority for System Exceptions.
	// Reset Handler, NMI,and HardFault has fixed priority.
	// SysTick priority s handled in HAL_Init()
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

	// Enable System Exceptions
	// Reset Handler, NMI,and HardFault are Enabled by default.
	// Enabling of SysTick is handled in HAL_Init()
	SCB->SHCSR |= ((SCB_SHCSR_MEMFAULTENA_Msk) |
				   (SCB_SHCSR_BUSFAULTENA_Msk) |
				   (SCB_SHCSR_USGFAULTENA_Msk));
}

/**
  * @brief  UART MSP Init.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *hUART)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if (USART2 == hUART->Instance)
	{
		// Tx and Rx Pins of UART2 peripheral in stm32f446re Nucleo boards
		// are connected to the onboard STLink circuitry which can be used as a USB to
		// Serial Interface for interfacing with PC or similar device

		__HAL_RCC_USART2_CLK_ENABLE();

		// UART2_TX amd UART2_RX are mapped to PA2 and PA3 respectively
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.Pin = (GPIO_PIN_2 | GPIO_PIN_3);
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *hUART)
{
	if (USART2 == hUART->Instance)
	{
		__HAL_RCC_USART2_CLK_DISABLE();
		HAL_GPIO_DeInit(GPIOA, (GPIO_PIN_2 | GPIO_PIN_3));
	}

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
