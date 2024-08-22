/*
 * The bus is a communication system that sends control signals and data between the processor and other components.
 * The main purpose for the bus will be to read and write.
 * */

#include "bus.h"

// Write a byte in a specific address to the bus
void BusWrite(Bus *bus, uint16_t address, uint8_t value) {
    // address >= 0x0000 && address <= 0xffff
    if (address < sizeof(bus->ram)) {
        bus->ram[address] = value;
    }
}

// Read a byte from the bus
uint8_t BusRead(Bus *bus, uint16_t address) {
    // address >= 0x0000 && address <= 0xffff
    if (address < sizeof(bus->ram)) {
        return bus->ram[address];
    }
    return 0x00;
}


