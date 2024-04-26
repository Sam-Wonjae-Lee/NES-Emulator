#pragma once
#include <stdint.h>     // For different integer types

/*
 * Addressing modes the 6502 CPU uses.
 * Each opcode (instruction) of the 6502 CPU has different ways of being processed and uses different addressing modes.
 *
 * https://www.nesdev.org/wiki/CPU_addressing_modes
 * */
enum AddressingMode {
    Implicit,
    Accumulator,
    Immediate,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Relative,
    Indirect,
    IndirectX,
    IndirectY
};

/*
 * 7 different flags for CPU flag to display current status
 * */
enum ProcessorFlag {
    Negative = 1 << 7,
    Overflow = 1 << 6,
    Unused  = 1 << 5,
    Break = 1 << 4,
    Decimal = 1 << 3,
    Interrupt = 1 << 2,
    Zero = 1 << 1,
    Carry = 0
};

class Bus;

class CPU {

/*
 * 6502 CPU has five 8-bit registers and one 16-bit register (Program Counter)
 *
 * https://www.nesdev.org/wiki/Programming_Basics
 * */
public:
    uint8_t Accumulator;    // Used to read and write to memory and store arithmetic and logic results
    uint8_t XIndex;     //
    uint8_t YIndex;
    uint8_t Flag;   // Represented as 7 different flags to show the status of the processor
    uint8_t StackPointer;   // Holds the address to the current location on the stack
    uint16_t ProgramCounter;    // Keeps track of the memory address of the next instruction to be executed

    AddressingMode AddressingMode;
    ProcessorFlag ProcessorFlag;

    void write(uint16_t address, uint8_t value);
    uint8_t read(uint16_t address);
    void ConnectToBus(Bus *bus);    // Connect CPU to bus

    // Addressing modes functions
    void IMP();
    void ACC();
    void IMM();
    void ZP();
    void ZPX();
    void ZPY();
    void ABS();
    void ABX();
    void ABY();
    void REL();
    void IND();
    void IZX();
    void IZY();

    // Opcodes functions
    void ADC();
    void AND();
    void ASL();
    void BCC();
    void BCS();
    void BEQ();
    void BIT();
    void BMI();
    void BNE();
    void BPL();
    void BRK();
    void BVC();
    void BVS();
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void CMP();
    void CPX();
    void CPY();
    void DEC();
    void DEX();
    void DEY();
    void EOR();
    void INC();
    void INX();
    void INY();
    void JMP();
    void JSR();
    void LDA();
    void LDX();
    void LDY();
    void LSR();
    void NOP();
    void ORA();
    void PHA();
    void PHP();
    void PLA();
    void PLP();
    void ROL();
    void ROR();
    void RTI();
    void RTS();
    void SBC();
    void SEC();
    void SED();
    void SEI();
    void STA();
    void STX();
    void STY();
    void TAX();
    void TAY();
    void TSX();
    void TXA();
    void TXS();
    void TYA();
};

