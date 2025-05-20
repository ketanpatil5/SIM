#include "main.h"
#include "sys_init.h"
char command[512];
char ATcommand[512];
uint8_t buffer[512];
char response[512];



int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_RTC_Init();

  uart_init();
  sprintf(command,"Start\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);
  rtc_int();
  sprintf(command,"RTC OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);

  gsm_init();
//  gsm_set_clock();
  sprintf(command,"GSM OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);
//while(1){
  data();
  sprintf(command,"JSON OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);
//  HAL_Delay(1000);
//  mqtt_subscribe("v1/devices/me/telemetry");
//  sprintf(command,"Subscribe OK\r\n");
//  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);

//}

//  send_certificate_to_modem();
//  char *phone ="+919405951862";
//  char *msg ="Hello World\x1A";
//  send_sms(phone, msg);
//  sprintf(command,"sms ok\r\n");
//  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);


}

