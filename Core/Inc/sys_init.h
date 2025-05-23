/*
 * sys_init.h
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#ifndef INC_SYS_INIT_H_
#define INC_SYS_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"  // Make sure to include the HAL header
#include "string.h"
#include "stdio.h"
#include "gsm.h"
#include "modbus.h"
#include "rtc.h"
#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "time.h"
#include "cJSON.h"
#include "address.h"
#include "sms.h"
#include "data.h"


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_RTC_Init(void);


extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern RTC_HandleTypeDef hrtc;


#ifdef __cplusplus
}
#endif

#endif /* INC_SYS_INIT_H_ */
