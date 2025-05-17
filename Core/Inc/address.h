/*
 * address.h
 *
 *  Created on: May 15, 2025
 *      Author: Admin
 */
#ifndef MODBUS_CONFIG_H
#define MODBUS_CONFIG_H

#include <stdint.h>

typedef struct {
    const char *key;
    uint8_t SlaveID;
    uint8_t Functioncode;
    uint16_t address;
    uint16_t length;
} ModbusRegister;

extern ModbusRegister registers[];
extern int numRegisters;

#endif
