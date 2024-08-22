/*
 * The bus is a communication system that sends control signals and data between the processor and other components.
 * The main purpose for the bus will be to read and write.
 * */

#pragma once
#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "cpu.h"

struct Bus {
    // Devices connected to the bus
    CPU cpu;
    uint8_t ram[1024 * 64];  // 64kb == 65536 bytes
}

void BusWrite(Bus *bus, uint16_t address, uint8_t value);
uint8_t BusRead(Bus *bus, uint16_t address);

#endif