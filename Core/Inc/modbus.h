/*
 * modbus.h
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#ifndef INC_MODBUS_H_
#define INC_MODBUS_H_

void modbus_init();
float modbus_float(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength);
int modbus_int(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength);
void write_Single_Reg(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data);
void write_Multiple_Reg(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data);
void write_Single_coil(uint8_t SlaveID, uint8_t FunctionCode, uint16_t Address, uint16_t Datalength, uint16_t Data);
//extern uint8_t RxData[256];
//extern uint8_t TxData[8];
//extern uint16_t Data[10];



#endif /* INC_MODBUS_H_ */
