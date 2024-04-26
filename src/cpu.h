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

/*
 * 6502 CPU has five 8-bit registers and one 16-bit register (Program Counter)
 *
 * https://www.nesdev.org/wiki/Programming_Basics
 * */
struct Register {
    uint8_t Accumulator;    // Used to read and write to memory and store arithmetic and logic results
    uint8_t XIndex;     //
    uint8_t YIndex;
    uint8_t Flag;   // Represented as 7 different flags to show the status of the processor
    uint8_t StackPointer;   // Holds the address to the current location on the stack
    uint16_t ProgramCounter;    // Keeps track of the memory address of the next instruction to be executed
};

class Bus;

class CPU {
public:
    Register CpuRegister;
    AddressingMode CpuAddressingMode;
    ProcessorFlag CpuProcessorFlag;

    Bus *bus;

    void Write(uint16_t address, uint8_t value);
    uint8_t Read(uint16_t address);
    void ConnectToBus(Bus *bus);    // Connect CPU to bus
    void Reset();

    // Addressing modes functions
    void AM_IMP();
    void AM_ACC();
    void AM_IMM();
    void AM_ZP0();
    void AM_ZPX();
    void AM_ZPY();
    void AM_REL();
    void AM_ABS();
    void AM_ABX();
    void AM_ABY();
    void AM_IND();
    void AM_INX();
    void AM_INY();

    // Opcodes functions
    void I_ADC();
    void I_AND();
    void I_ASL();
    void I_BCC();
    void I_BCS();
    void I_BEQ();
    void I_BIT();
    void I_BMI();
    void I_BNE();
    void I_BPL();
    void I_BRK();
    void I_BVC();
    void I_BVS();
    void I_CLC();
    void I_CLD();
    void I_CLI();
    void I_CLV();
    void I_CMP();
    void I_CPX();
    void I_CPY();
    void I_DEC();
    void I_DEX();
    void I_DEY();
    void I_EOR();
    void I_INC();
    void I_INX();
    void I_INY();
    void I_JMP();
    void I_JSR();
    void I_LDA();
    void I_LDX();
    void I_LDY();
    void I_LSR();
    void I_NOP();
    void I_ORA();
    void I_PHA();
    void I_PHP();
    void I_PLA();
    void I_PLP();
    void I_ROL();
    void I_ROR();
    void I_RTI();
    void I_RTS();
    void I_SBC();
    void I_SEC();
    void I_SED();
    void I_SEI();
    void I_STA();
    void I_STX();
    void I_STY();
    void I_TAX();
    void I_TAY();
    void I_TSX();
    void I_TXA();
    void I_TXS();
    void I_TYA();
};

