/*
 * The cpu used in the NES is known as the Ricoh 2A03 which is based on the MOS Technology 6502 processor.
 * The cpu contains information on addressing modes, registers, and opcodes.
 * */

#include <stdint.h>
#include "cpu.h"
#include "bus.h"

#include <iostream>

void CPU::Write(uint16_t address, uint8_t value) {
    bus->Write(address, value);
}

uint8_t CPU::Read(uint16_t address) {
    return bus->Read(address, false);
}

void CPU::ConnectToBus(Bus *bus) {

}

//void CPU::Reset() {
//    CpuRegister.StackPointer = 0xFD;
//}

// Set Carry Flag
// Set the Carry Flag to 1
void CPU::SEC() {
    std::cout << "Carry flag before SEC: " << ((CpuRegister.Flag >> ProcessorFlag::Carry) & 1) << std::endl;

    CpuRegister.Flag |= (1 << ProcessorFlag::Carry);

    std::cout << "Carry flag after SEC: " << ((CpuRegister.Flag >> ProcessorFlag::Carry) & 1) << std::endl;
}
