#include "uart.h"
//#include "error_handler.h"
#include <stdio.h>

UART_HandleTypeDef UartHandle;

#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


void uart_init(void){

	  /* - Hardware flow control disabled (RTS and CTS signals)
	   *  RTS (Request to Send) and CTS (Clear to Send) are two control lines used for hardware flow control.
	   *  RTS: The sender (transmitter) asserts this signal to indicate that it is ready to send data.
	   *  CTS: The receiver (or the device at the receiving end) asserts this signal to indicate that it is ready to receive data.
	   *  When hardware flow control is enabled, the sender waits for a CTS signal from the receiver before transmitting data.
	   *  Similarly, the receiver checks the RTS signal to determine when it is ready to accept new data.*/

	  UartHandle.Instance          = USART2;

	  UartHandle.Init.BaudRate     = 9600;
	  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartHandle.Init.Parity       = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode         = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if(HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
//	    Error_Handler();
	  }

	  /* Output a message on Hyperterminal using printf function */
	  printf("\n\r UART Printf Example: retarget the C library printf function to the UART 5555555\n\r");

}



PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


#ifdef  USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
