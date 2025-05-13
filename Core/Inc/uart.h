/*
 * uart.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Admin
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"  // Make sure to include the HAL header
//#include "stm32f4xx_nucleo.h" // for LED2

void uart_init(void); // Declare the uart_init function
extern UART_HandleTypeDef UartHandle;
#ifdef __cplusplus
}
#endif


#endif /* INCLUDE_UART_H_ */
