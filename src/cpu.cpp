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

void CPU::Reset() {
    CpuRegister.ProgramCounter = 0xFFFC;
    CpuRegister.ProgramCounter = 0x00FF;
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Carry);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Interrupt);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Decimal);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Break);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Overflow);
    CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
}

void CPU::Step() {

}

// ---------- Addressing Modes Functions Start ----------

// Implicit
void CPU::IMP() {
    CpuAddressingMode = Implicit;
}

// Accumulator
void CPU::ACC() {
    CurrentValue = CpuRegister.Accumulator;
    CpuAddressingMode = Accumulator;
}

// Immediate
void CPU::IMM() {
    CurrentAddress = CpuRegister.ProgramCounter++;
    CurrentValue = Read(CurrentAddress);
    CpuAddressingMode = Immediate;
}

// ---------- Addressing Modes Functions End ----------
// ---------- Opcode Functions Start ----------

// Branch if Carry Clear
void CPU::BCC() {

}

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

// Decrement X Register
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

// Decrement Y Register
void CPU::DEY() {
    // Decrement X register
    CpuRegister.YIndex--;
    cycles += 2;

    if (CpuRegister.YIndex == 0x00) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }

    if ((CpuRegister.YIndex & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }
}

// Increment X Register
void CPU::INX() {
    // Increment X register
    CpuRegister.XIndex++;
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

// Increment Y Register
void CPU::INY() {
    // Increment X register
    CpuRegister.YIndex++;
    cycles += 2;

    if (CpuRegister.YIndex == 0x00) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }

    if ((CpuRegister.YIndex & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }
}

// Jump
void CPU::JMP() {
    // Set program counter to the address specified
    CpuRegister.ProgramCounter = CurrentAddress;
    if (CpuAddressingMode == Absolute) {
        cycles += 3;
    } else if (CpuAddressingMode == Indirect) {
        cycles += 5;
    }
}

// Jump to Subroutine
void CPU::JSR() {

}

// TODO: Finish LDA with Addressing Modes
// Load Accumulator
void CPU::LDA() {
    // Loads a byte of memory into the accumulator
    CpuRegister.Accumulator = CurrentValue;
    if (CpuRegister.Accumulator == 0) {
        // Set Zero Flag to 1 if Accumulator == 0
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else if ((CpuRegister.Accumulator & 0b10000000) > 0) {
        // Set Negative Flag to 1 if the bit 7 of Accumulator is set
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
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

// Transfer Accumulator to Y
void CPU::TAY() {
    // Y = A
    CpuRegister.YIndex = CpuRegister.Accumulator;

    if ((CpuRegister.YIndex & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }

    if (CpuRegister.YIndex == 0) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }
    cycles += 2;
}

// Transfer Stack Pointer to X
void CPU::TSX() {
    // X = SP
    CpuRegister.XIndex = CpuRegister.StackPointer;

    if ((CpuRegister.XIndex & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }

    if (CpuRegister.XIndex == 0) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }
    cycles += 2;
}

// Transfer X to Accumulator
void CPU::TXA() {
    // A = X
    CpuRegister.Accumulator = CpuRegister.XIndex;

    if ((CpuRegister.Accumulator & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }

    if (CpuRegister.Accumulator == 0) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }
    cycles += 2;
}

// Transfer X to Stack Pointer
void CPU::TXS() {
    // SP = X
    CpuRegister.StackPointer = CpuRegister.XIndex;
    cycles += 2;
}

// Transfer Y to Accumulator
void CPU::TYA() {
    // A = Y
    CpuRegister.Accumulator = CpuRegister.YIndex;

    if ((CpuRegister.Accumulator & 0x80) >> 7) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Negative);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Negative);
    }

    if (CpuRegister.Accumulator == 0) {
        CpuRegister.Flag |= (1 << ProcessorFlag::Zero);
    } else {
        CpuRegister.Flag &= ~(1 << ProcessorFlag::Zero);
    }
    cycles += 2;
}

// ---------- Opcode Functions End ----------
