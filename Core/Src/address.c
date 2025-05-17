/*
 * address.c
 *
 *  Created on: May 15, 2025
 *      Author: Admin
 */
#include "main.h"
#include "sys_init.h"

#include <stdint.h>

//typedef struct {
//    const char *key;
//    uint8_t SlaveID;
//    uint8_t Functioncode;
//    uint16_t address;
//    uint16_t length;
//} ModbusRegister;

ModbusRegister registers[] = {
    { "temperature", 1, 4, 104, 1 },
    { "humidity",    1, 4, 105, 1 },
    { "flow",        1, 4, 107, 1 },
    { "pressure",    1, 4, 108, 1 }
};

int numRegisters = sizeof(registers) / sizeof(registers[0]);



