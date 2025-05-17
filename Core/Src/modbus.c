/*
 * modbus.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#include "main.h"
#include "sys_init.h"
#include "modbus_crc.h"
uint8_t RxData[256];
uint8_t TxData[8];
uint16_t Data[10];

float  IEEE754tofloat(uint32_t value) {
	union {
	        float f;
	        uint32_t bytes;
	    } u;
	    u.bytes = value;
    return u.f;
}



void sendData (uint8_t *data)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart3, data, 8, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}


float modbus_float(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength){

	float value = 0;
	TxData[0] = SlaveID& 0xFF;  // slave address
	TxData[1] = FunctionCode& 0xFF; // Function Code
	//Address
	TxData[2] = (Address >> 8) & 0xFF;  // High byte
	TxData[3] = Address & 0xFF;         // Low byte
	//Datalength
	TxData[4] = (Datalength >> 8) & 0xFF;  // High byte
	TxData[5] = Datalength & 0xFF;         // Low byte

	uint16_t crc = crc16(TxData, 6);
	TxData[6] = crc&0xFF;   // CRC LOW
	TxData[7] = (crc>>8)&0xFF;  // CRC HIGH

	sendData(TxData);



    uint8_t response_length = 5 + 2 * Datalength;
    if (HAL_UART_Receive(&huart3, RxData, response_length, 100) == HAL_OK) {
        // Check CRC
        uint16_t resp_crc = crc16(RxData, response_length - 2);
        uint16_t received_crc = (RxData[response_length - 1] << 8) | RxData[response_length - 2];
        if (resp_crc == received_crc) {
            // Extract data
            uint32_t raw = (RxData[3] << 24) | (RxData[4] << 16) | (RxData[5] << 8) | RxData[6];

            value = IEEE754tofloat(raw & 0xFFFFFFFF);
        } else {
            // CRC error
            return -1;
        }
    } else {
        // Timeout or communication error
        return -2;
    }

    return value;

}

int modbus_int(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength) {

    int value = 0;

    // Construct Modbus RTU request
    TxData[0] = SlaveID;
    TxData[1] = FunctionCode;
    TxData[2] = (Address >> 8) & 0xFF;     // Address high byte
    TxData[3] = Address & 0xFF;            // Address low byte
    TxData[4] = (Datalength >> 8) & 0xFF;  // Quantity high byte
    TxData[5] = Datalength & 0xFF;         // Quantity low byte


    // Calculate CRC
    uint16_t crc = crc16(TxData, 6);
    TxData[6] = crc & 0xFF;          // CRC low byte
    TxData[7] = (crc >> 8) & 0xFF;   // CRC high byte

    // Send the Modbus frame
    sendData(TxData);
    // Wait and receive the response using polling
    // Expected response size: 5 (header) + 2 * Datalength + 2 (CRC)
    uint8_t response_length = 5 + 2 * Datalength ;
    if (HAL_UART_Receive(&huart3, RxData, response_length, 100) == HAL_OK) {
        // Check CRC
        uint16_t resp_crc = crc16(RxData, response_length - 2);
        uint16_t received_crc = (RxData[response_length - 1] << 8) | RxData[response_length - 2];
        if (resp_crc == received_crc) {
            // Extract data
            uint16_t raw = (RxData[3] << 8) | RxData[4];
            value = (int)raw;
        } else {
            // CRC error
            return -1;
        }
    } else {
        // Timeout or communication error
        return -2;
    }

    return value;
}

void write_Single_Reg(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data)
{
	// Prepare Response

	TxData[0] = SlaveID & 0xFF;    // slave ID
	TxData[1] = FunctionCode & 0xFF;   // function code
    TxData[2] = (Address >> 8) & 0xFF;     // Address high byte
    TxData[3] = Address & 0xFF;            // Address low byte
    TxData[4] = (Datalength >> 8) & 0xFF;  // Quantity high byte
    TxData[5] = Datalength & 0xFF;         // Quantity low byte
    TxData[6] = Datalength; // Byte count (3 Registers would need 6 bytes (2 bytes per register))
    TxData[7] = (Data >> 8) & 0xFF;  // Quantity high byte
    TxData[8] = Data & 0xFF;         // Quantity low byte

    // Calculate CRC
    uint16_t crc = crc16(TxData, 9);
    TxData[9] = crc & 0xFF;          // CRC low byte
    TxData[10] = (crc >> 8) & 0xFF;   // CRC high byte

    sendData(TxData);  // send data... CRC will be calculated in the function itself
	   // success
}

void write_Multiple_Reg(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data)
{
	// Prepare Response

	TxData[0] = SlaveID & 0xFF;    // slave ID
	TxData[1] = FunctionCode & 0xFF;   // function code
    TxData[2] = (Address >> 8) & 0xFF;     // Address high byte
    TxData[3] = Address & 0xFF;            // Address low byte
    TxData[4] = (Datalength >> 8) & 0xFF;  // Quantity high byte
    TxData[5] = Datalength & 0xFF;         // Quantity low byte
    TxData[6] = Datalength*2; // Byte count (3 Registers would need 6 bytes (2 bytes per register))
    TxData[7] = (Data >> 8) & 0xFF;  // Quantity high byte
    TxData[8] = Data & 0xFF;         // Quantity low byte
    TxData[9] = (Data >> 8) & 0xFF;  // Quantity high byte
    TxData[10] = Data & 0xFF;         // Quantity low byte

    // Calculate CRC
    uint16_t crc = crc16(TxData, 11);
    TxData[11] = crc & 0xFF;          // CRC low byte
    TxData[12] = (crc >> 8) & 0xFF;   // CRC high byte

    sendData(TxData);  // send data... CRC will be calculated in the function itself
	   // success

}

void write_Single_coil(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data)
{
	// Prepare Response

	TxData[0] = SlaveID & 0xFF;    // slave ID
	TxData[1] = FunctionCode & 0xFF;   // function code
    TxData[2] = (Address >> 8) & 0xFF;     // Address high byte
    TxData[3] = Address & 0xFF;            // Address low byte
    TxData[4] = (Datalength >> 8) & 0xFF;  // Quantity high byte
    TxData[5] = Datalength & 0xFF;         // Quantity low byte
    TxData[6] = Datalength; // Byte count (3 Registers would need 6 bytes (2 bytes per register))
    TxData[7] = (Data >> 8) & 0xFF;  // Quantity high byte
    TxData[8] = Data & 0xFF;         // Quantity low byte

    // Calculate CRC
    uint16_t crc = crc16(TxData, 9);
    TxData[9] = crc & 0xFF;          // CRC low byte
    TxData[10] = (crc >> 8) & 0xFF;   // CRC high byte

    sendData(TxData);  // send data... CRC will be calculated in the function itself
}

