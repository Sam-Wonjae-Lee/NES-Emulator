/*
 * The cpu used in the NES is known as the Ricoh 2A03 which is based on the MOS Technology 6502 processor.
 * The cpu contains information on addressing modes, registers, and opcodes.
 * */

#include <stdint.h>
#include "cpu.h"
#include "bus.h"

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

// Force Interrupt
// Forces the generation of an interrupt request
void CPU::BRK() {
    // Set the Break Flag to 1
    CpuRegister.Flag |= (1 << ProcessorFlag::Break);
    cycles += 7;
}

// Clear Carry Flag
void CPU::CLC() {
    // Set Carry Flag to 0
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Carry);
    cycles += 2;
}

// Clear Decimal Mode
void CPU::CLD() {
    // Set Decimal Mode Flag to 0
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Decimal);
    cycles += 2;
}

// Clear Interrupt Disable
void CPU::CLI() {
    // Set Interrupt Disable Flag to 0
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Interrupt);
    cycles += 2;
}

// Clear Overflow Flag
void CPU::CLV() {
    // Set Overflow Flag to 0
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Overflow);
    cycles += 2;
}

void CPU::DEX() {
    // Decrement X register
    CpuRegister.XIndex--;
    cycles += 2;

    if (CpuRegister.XIndex == 0x00) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }

    if ((CpuRegister.XIndex & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }
}

// Set Carry Flag
void CPU::SEC() {
    // Set the Carry Flag to 1
    CpuRegister.Flag |= (1 << ProcessorFlag::Carry);
    cycles += 2;
}

// Set Decimal Flag
void CPU::SED() {
    // Set the Decimal Mode Flag to 1
    CpuRegister.Flag |= (1 << ProcessorFlag::Decimal);
    cycles += 2;
}

// Set Interrupt Disable
void CPU::SEI() {
    // Set the Interrupt Disable Flag to 1
    CpuRegister.Flag |= (1 << ProcessorFlag::Interrupt);
    cycles += 2;
}

