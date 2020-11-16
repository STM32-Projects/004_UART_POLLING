/**
  ******************************************************************************
  * @file    main.c
  * @author  Supreeth
  * @version V1.0
  * @date    01-December-2013
  *
  * @brief   Sending characters over UART in polling mode
  *
  * Overview
  * --------
  *
  * This application sends a welcome message over UART2 at every 500ms
  * time interval in a busy-wait manner.
  *
  * Note 1: Tx and Rx Pins of UART2 peripheral in stm32f446re Nucleo boards
  * are connected to the onboard STLink circuitry which can be used as a USB to
  * Serial Interface for interfacing with PC or similar devices.
  *
  * Note 2: Whenever we connect the Nucleo board to PC, it is enumerated as a
  * Virtual COM Port. To find out the port which it is connected to, we can
  * do the following:
  *
  * i)  On Windows Systems: Open Device Manager. Look in the Device Manager
  *     list, open the category "Ports" and find the matching COM Port.
  *
  *     E.g: COM8
  *
  * ii) On Linux Systems: Open terminal and type in
  *
  *     dmesg | grep tty
  *
  *     This will you the tell the tty interface it is connected to.
  *
  *     E.g ttyUSB0
  *
  * Runs on stm32f446re
  *
  ******************************************************************************
*/

#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

// Make UART2 handle global as it is used in other files for low
// level initialization
UART_HandleTypeDef hUART2;

void UART2_Init();
void ErrorHandler();

int main(void)
{
	char *msg = "hahahahahahahaha................\n\r";

	HAL_Init();
	UART2_Init();

	for(;;)
	{
		HAL_UART_Transmit(&hUART2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		HAL_Delay(500);
	}
}

/**
 * @brief UART2 Initialization Routine
 *
 * @param   None
 * @return 	None
 *
 * @note 	Tx and Rx Pins of UART2 peripheral in stm32f446re Nucleo boards
 * 			are connected to the onboard STLink circuitry which can be used as a USB to
 * 			Serial Interface for interfacing with PC or similar devices
 */
void UART2_Init()
{
	hUART2.Instance = USART2;
	hUART2.Init.BaudRate = 9600;
	hUART2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hUART2.Init.Mode = UART_MODE_TX_RX;
	hUART2.Init.Parity = UART_PARITY_NONE;
	hUART2.Init.StopBits = UART_STOPBITS_1;
	hUART2.Init.WordLength = UART_WORDLENGTH_8B;

	if (HAL_UART_Init(&hUART2) != HAL_OK) {
		ErrorHandler();
	}
}


/**
 * @brief Error Handler to be invoked in case of HAL Init failures
 *
 * @param  None
 * @return None
 *
 */

void ErrorHandler()
{
	//TODO: Do something useful instead of wasting CPU cycles
	for (;;);
}
