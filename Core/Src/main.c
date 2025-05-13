#include "main.h"
#include "sys_init.h"
#include "gsm.h"
#include "modbus.h"
#include "sms.h"


int main(void)
{
//	  char mobileNumber[] = "+919405951862";
	  char ATcommand[80];
//	  uint8_t buffer[30] = {0};
//	  uint8_t ATisOK = 0;
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  modbus_init();
  sprintf(ATcommand,"modbus OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
  gsm_init();
  sprintf(ATcommand,"gsm ok\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
  char *phone ="+919405951862";
  char *msg ="Hello World\x1A";
  send_sms(phone, msg);
  sprintf(ATcommand,"sms ok\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);

//  while(!ATisOK){
//    sprintf(ATcommand,"AT\r\n");
//    HAL_UART_Transmit(&huart1,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//    HAL_UART_Receive(&huart1, buffer, 30, 100);
//    HAL_Delay(1000);
//    sprintf(ATcommand,"AT\r\n");
//    HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//    if(strstr((char *)buffer,"OK")){
//      ATisOK = 1;
//      sprintf(ATcommand,"AT2\r\n");
//      HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//    }
//    HAL_Delay(1000);
//    memset(buffer,0,sizeof(buffer));
//  }
//
//  sprintf(ATcommand,"AT+CMGF=1\r\n");
//  HAL_UART_Transmit(&huart1,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//  HAL_UART_Receive(&huart1, buffer, 30, 100);
//  HAL_Delay(1000);
//  memset(buffer,0,sizeof(buffer));
//
//  sprintf(ATcommand,"AT+CMGS=\"%s\"\r\n",mobileNumber);
//  HAL_UART_Transmit(&huart1,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//  HAL_Delay(100);
//  sprintf(ATcommand,"Hello World, STM32 started%c",0x1a);
//  HAL_UART_Transmit(&huart1,(uint8_t *)ATcommand,strlen(ATcommand),1000);
//  HAL_UART_Receive(&huart1, buffer, 30, 100);
//  memset(buffer,0,sizeof(buffer));
//  HAL_Delay(4000);
}



