/*
 * modbus.h
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#ifndef INC_MODBUS_H_
#define INC_MODBUS_H_

void modbus_init();
float modbus_float(uint8_t SlaveID, uint8_t FunctionCode, uint8_t Address, uint8_t Datalength);
int modbus_int(uint8_t SlaveID, uint8_t FunctionCode, uint8_t Address, uint8_t Datalength);
extern uint8_t RxData[32];
extern uint8_t TxData[8];
extern uint16_t Data[10];



#endif /* INC_MODBUS_H_ */
