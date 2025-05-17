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
  gsm_set_clock();
  sprintf(command,"GSM OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);
//while(1){
//  data();
//  sprintf(command,"JSON OK\r\n");
//  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);
//  HAL_Delay(1000);
  mqtt_subscribe("v1/devices/me/telemetry");
  sprintf(command,"Subscribe OK\r\n");
  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);

//}

//  send_certificate_to_modem();
//  char *phone ="+919405951862";
//  char *msg ="Hello World\x1A";
//  send_sms(phone, msg);
//  sprintf(command,"sms ok\r\n");
//  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);


}




//#include "main.h"
//#include "stm32f4xx_hal.h"  // Change if needed for your MCU
//#include "sys_init.h"
//#define CMD_BUFFER_SIZE 128
//
//uint8_t console_rx_byte;
//uint8_t sim_rx_byte;
//char console_cmd_buffer[CMD_BUFFER_SIZE];
//uint8_t cmd_index = 0;
//
//void Start_UART_CommandBridge(void) {
//    HAL_UART_Receive_IT(&huart2, &console_rx_byte, 256);  // Start receiving from console
//    HAL_UART_Receive_IT(&huart1, &sim_rx_byte, 256);      // Start receiving from SIM
//}
//
//void ProcessConsoleInput(uint8_t byte) {
//    if (byte == '\r' || byte == '\n') {
//        if (cmd_index > 0) {
//            console_cmd_buffer[cmd_index++] = '\r';  // SIM expects CR
//            HAL_UART_Transmit(&huart1, (uint8_t *)console_cmd_buffer, cmd_index, HAL_MAX_DELAY);
//            cmd_index = 0;
//        }
//    } else if (cmd_index < CMD_BUFFER_SIZE - 2) {
//        console_cmd_buffer[cmd_index++] = byte;
//    }
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//    if (huart == &huart2) {
//        ProcessConsoleInput(console_rx_byte);
//        HAL_UART_Receive_IT(&huart2, &console_rx_byte, 1);  // Continue listening
//    } else if (huart == &huart1) {
//        HAL_UART_Transmit(&huart2, &sim_rx_byte, 1, HAL_MAX_DELAY);  // Forward response
//        HAL_UART_Receive_IT(&huart1, &sim_rx_byte, 1);               // Continue listening
//    }
//}
//
//int main(void)
//{
//    HAL_Init();
//    SystemClock_Config();
//    MX_GPIO_Init();
//    MX_USART1_UART_Init();  // SIM module
//    MX_USART2_UART_Init();  // Console
//    Start_UART_CommandBridge();  // <-- Start the UART bridge
//
//    while (1)
//    {
//
//        // You can keep this empty or use it for status indicators
//    }
//}
