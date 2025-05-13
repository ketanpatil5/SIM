#include "main.h"
#include "sys_init.h"
#include "gsm.h"
#include "modbus.h"
#include "sms.h"
#include "data.h"

int main(void)
{
  char ATcommand[80];
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
//  modbus_init();
//  uint8_t SlaveID = 0x01;
//  uint8_t FunctionCode = 0x04;
//  uint8_t Address = 100;
//  uint8_t Datalength = 2;


  gsm_init();
  sprintf(ATcommand,"gsm ok\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
  data();
//  modbus(SlaveID,FunctionCode,Address,Datalength);
  sprintf(ATcommand,"modbus OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);
  char *phone ="+919405951862";
  char *msg ="Hello World\x1A";
  send_sms(phone, msg);
  sprintf(ATcommand,"sms ok\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)ATcommand,strlen(ATcommand),1000);


}



