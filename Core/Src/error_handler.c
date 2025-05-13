/*
 * error_handler.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */
#include "error_handler.h"
#include "sys_init.h"

void Error_Handler(void)
{
	__disable_irq();
	char Error[80];
    sprintf(Error,"ERROR\r\n");
    HAL_UART_Transmit(&huart2,(uint8_t *)Error,strlen(Error),1000);
//  HAL_NVIC_SystemReset();
  while(1)
  {
  }
}


