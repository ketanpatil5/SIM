/*
 * modbus.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#include "main.h"
#include "sys_init.h"
#include "modbus_crc.h"
uint8_t RxData[32];
uint8_t TxData[8];
uint16_t Data[10];
float DataM;

float  IEEE754tofloat(uint32_t value) {
	union {
	        float f;
	        uint32_t bytes;
	    } u;
	    u.bytes = value;
    return u.f;
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	Data[0] = RxData[3]<<8 | RxData[4];
	Data[1] = RxData[5]<<8 | RxData[6];
	Data[2] = RxData[7]<<8 | RxData[8];
	Data[3] = RxData[9]<<8 | RxData[10];
//	Data[4] = RxData[11]<<8 | RxData[12];
}

void sendData (uint8_t *data)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart3, data, 8, 1000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void modbus_init(){
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxData, 32);

	  TxData[0] = 0x01;  // slave address
	//  TxData[1] = 0x03;  // Function code for Read Holding Registers
	  TxData[1] = 0x04;  // Function code for Read Input Registers

	  /*
	   * The function code 0x03 means we are reading Holding Registers
	   * The Register address ranges from 40001 - 50000
	   * The register address we input can range from 0-9999 (0x00-0x270F)
	   * Here 0 corresponds to the Address 40001 and 9999 corresponds to 50000
	   * Although we can only read 125 registers sequentially at once
	   */
	//  TxData[2] = 0;
	//  TxData[3] = 0x04;
	//  //The Register address will be 00000000 00000100 = 4 + 40001 = 40005

	  TxData[2] = 0;
	  TxData[3] = 0x64;
	  //The Register address will be 00000000 00000001 = 1 +30001 = 30002

	  TxData[4] = 0;
	  TxData[5] = 0x02;
	  // no of registers to read will be 00000000 00000101 = 5 Registers = 10 Bytes

	  uint16_t crc = crc16(TxData, 6);
	  TxData[6] = crc&0xFF;   // CRC LOW
	  TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

	  sendData(TxData);
}

float modbus_float(uint8_t SlaveID, uint8_t FunctionCode, uint8_t Address, uint8_t Datalength){
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxData, 32);
	TxData[0] = SlaveID;  // slave address
	switch (FunctionCode)
	    {
	        case 0x01:  // Read Coils
	        	TxData[1] = 0x01;
	            break;

	        case 0x02:  // Read Discrete Inputs
	        	TxData[1] = 0x02;
	            break;

	        case 0x03:  // Read Holding Registers
	        	TxData[1] = 0x03;
	            break;

	        case 0x04:  // Read Input Registers
	        	TxData[1] = 0x04;
	            break;

	        default:
	        	TxData[1] = 0x04;
	            break;
	    }
	//Address
	TxData[4] = (Address >> 8) & 0xFF;  // High byte
	TxData[5] = Address & 0xFF;         // Low byte
	//Datalength
	TxData[4] = (Datalength >> 8) & 0xFF;  // High byte
	TxData[5] = Datalength & 0xFF;         // Low byte

	uint16_t crc = crc16(TxData, 6);
	TxData[6] = crc&0xFF;   // CRC LOW
	TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

	sendData(TxData);

		return IEEE754tofloat((Data[0]<<16|Data[1])& 0xFFFFFFFF);



}

int modbus_int(uint8_t SlaveID, uint8_t FunctionCode, uint8_t Address, uint8_t Datalength){
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, RxData, 32);
	TxData[0] = SlaveID;  // slave address
	switch (FunctionCode)
	    {
	        case 0x01:  // Read Coils
	        	TxData[1] = 0x01;
	            break;

	        case 0x02:  // Read Discrete Inputs
	        	TxData[1] = 0x02;
	            break;

	        case 0x03:  // Read Holding Registers
	        	TxData[1] = 0x03;
	            break;

	        case 0x04:  // Read Input Registers
	        	TxData[1] = 0x04;
	            break;

	        default:
	        	TxData[1] = 0x04;
	            break;
	    }
	//Address
	TxData[4] = (Address >> 8) & 0xFF;  // High byte
	TxData[5] = Address & 0xFF;         // Low byte
	//Datalength
	TxData[4] = (Datalength >> 8) & 0xFF;  // High byte
	TxData[5] = Datalength & 0xFF;         // Low byte

	uint16_t crc = crc16(TxData, 6);
	TxData[6] = crc&0xFF;   // CRC LOW
	TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

	sendData(TxData);

		return Data[0];



}
