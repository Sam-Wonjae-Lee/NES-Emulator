#include <stdint.h>


/*
 * Addressing modes the 6502 CPU uses.
 * Each opcode (instruction) of the 6502 CPU has different ways of being processed and uses different addressing modes.
 *
 * https://www.nesdev.org/wiki/CPU_addressing_modes
 * */
enum AddressingMode {
    Accumulator,
    Relative,
    Immediate,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    IndirectX,
    IndirectY,
    NoneAddressing
};

/*
 * https://www.nesdev.org/wiki/CPU_unofficial_opcodes
 * */
enum OpCode {

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
    Carry = 1 << 0
};

/*
 * 6502 CPU has five 8-bit registers and one 16-bit register (Program Counter)
 *
 * https://www.nesdev.org/wiki/Programming_Basics
 * */
struct CPU {
    uint8_t Accumulator;    // Used to read and write to memory and store arithmetic and logic results
    uint8_t XIndex;     //
    uint8_t YIndex;
    uint8_t Flag;   // Represented as 7 different flags to show the status of the processor
    uint8_t StackPointer;   // Holds the address to the current location on the stack
    uint16_t ProgramCounter;    // Keeps track of the memory address of the next instruction to be executed
};


