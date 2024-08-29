/*
 * The cpu used in the NES is known as the Ricoh 2A03 which is based on the MOS Technology 6502 processor.
 * The cpu is the main processor chip and contains information on addressing modes, registers, and opcodes.
 * */

#pragma once
#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>

// Opcodes functions
// https://www.oxyron.de/html/opcodes02.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html
typedef enum {
    ADC,     // Add with carry
    AND,     // Logical And (And With Accumulator)
    ASL,     // Arithmetic Shift Left
    BCC,     // Branch if Carry Clear
    BCS,     // Branch if Carry Set
    BEQ,     // Branch if Equal
    BIT,     // Bit Test
    BMI,     // Branch if Minus
    BNE,     // Branch if Not Equal
    BPL,     // Branch if Positive
    BRK,     // Force Interrupt
    BVC,     // Branch if Overflow Clear
    BVS,     // Branch if Overflow Set
    CLC,     // Clear Carry Flag
    CLD,     // Clear Decimal Mode
    CLI,     // Clear Interrupt Disable
    CLV,     // Clear Overflow Flag
    CMP,     // Compare
    CPX,     // Compare X Register
    CPY,     // Compare Y Register
    DEC,     // Decrement Memory
    DEX,     // Decrement X Register
    DEY,     // Decrement Y Register
    EOR,     // Exclusive OR
    INC,     // Increment Memory
    INX,     // Increment X Register
    INY,     // Increment Y Register
    JMP,     // Jump
    JSR,     // Jump to Subroutine
    LDA,     // Load Accumulator
    LDX,     // Load X Register
    LDY,     // Load Y Register
    LSR,     // Logical Shift Right
    NOP,     // No Operation
    ORA,     // Logical Inclusive Or
    PHA,     // Push Accumulator
    PHP,     // Push Processor Status
    PLA,     // Pull Accumulator
    PLP,     // Pull Processor Status
    ROL,     // Rotate Left
    ROR,     // Rotate Right
    RTI,     // Return from Interrupt
    RTS,     // Return from Subroutine
    SBC,     // Subtract with Carry
    SEC,     // Set Carry Flag
    SED,     // Set Decimal Flag
    SEI,     // Set Interrupt Flag
    STA,     // Store Accumulator
    STX,     // Store X Register
    STY,     // Store Y Register
    TAX,     // Transfer Accumulator to X
    TAY,     // Transfer Accumulator to Y
    TSX,     // Transfer Stack Pointer to X
    TXA,     // Transfer X to Accumulator
    TXS,     // Transfer X to Stack Pointer
    TYA,     // Transfer X to Accumulators

    // Unofficial opcodes
    ALR,
    ANC,
    ARR,
    AXS,
    LAX,
    LAS,
    SAX,
    SHY,
    SHX,

    DCP,
    ISC,
    RLA,
    RRA,
    SLO,
    SRE,

    SKB,
    IGN,
} Opcode;


/*
 * Addressing modes the 6502 CPU uses.
 * Each opcode (instruction) of the 6502 CPU has different ways of being processed and uses different addressing modes.
 *
 * https://www.nesdev.org/wiki/CPU_addressing_modes
 * */
typedef enum {
    None, 
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
} AddressingMode;


typedef struct {
    Opcode opcode;
    AddressingMode mode;
} Instruction;

// https://www.nesdev.org/wiki/CPU_unofficial_opcodes
// https://www.oxyron.de/html/opcodes02.html
const Instruction OpcodeMatrix[256] = {
    {BRK, Implicit}, {ORA, IndirectX}, {NOP, None}, {SLO, IndirectX}, {NOP, ZeroPage}, {ORA, ZeroPage}, {ASL, ZeroPage}, {SLO, ZeroPage}, {PHP, Implicit}, {ORA, Immediate}, {ASL, Implicit}, {ANC, Immediate}, {NOP, Absolute}, {ORA, Absolute}, {ASL, Absolute}, {SLO, Absolute},
    {BPL, Relative}, {ORA, IndirectY}, {NOP, None}, {SLO, IndirectY}, {NOP, ZeroPageX}, {ORA, ZeroPageX}, {ASL, ZeroPageX}, {SLO, ZeroPageX}, {CLC, Implicit}, {ORA, AbsoluteY}, {NOP, Implicit}, {SLO, AbsoluteY}, {NOP, AbsoluteX}, {ORA, AbsoluteX}, {ASL, AbsoluteX}, {SLO, AbsoluteX},
    {JSR, Absolute}, {AND, IndirectX}, {NOP, None}, {RLA, IndirectX}, {BIT, ZeroPage}, {AND, ZeroPage}, {ROL, ZeroPage}, {RLA, ZeroPage}, {PLP, Immediate}, {AND, Immediate}, {ROL, Implicit}, {ANC, Immediate}, {BIT, Absolute}, {AND, Absolute}, {ROL, Absolute}, {RLA, Absolute},
    {BMI, Relative}, {AND, IndirectY}, {NOP, None}, {RLA, IndirectY}, {NOP, ZeroPageX}, {AND, ZeroPageX}, {ROL, ZeroPageX}, {RLA, ZeroPageX}, {SEC, Implicit}, {AND, AbsoluteY}, {NOP, Immediate}, {RLA, AbsoluteY}, {NOP, AbsoluteX}, {AND, AbsoluteX}, {ROL, AbsoluteX}, {RLA, AbsoluteX},
    {RTI, Implicit}, {EOR, IndirectX}, {NOP, None}, {SRE, IndirectX}, {NOP, ZeroPage}, {EOR, ZeroPage}, {LSR, ZeroPage}, {SRE, ZeroPage}, {PHA, Implicit}, {EOR, Immediate}, {LSR, Implicit}, {ALR, Immediate}, {JMP, Absolute}, {EOR, Absolute}, {LSR, Absolute}, {SRE, Absolute},
    {BVC, Relative}, {EOR, IndirectY}, {NOP, None}, {SRE, IndirectY}, {NOP, ZeroPageX}, {EOR, ZeroPageX}, {LSR, ZeroPageX}, {SRE, ZeroPageX}, {CLI, Implicit}, {EOR, AbsoluteY}, {NOP, Implicit}, {SRE, AbsoluteY}, {NOP, AbsoluteX}, {EOR, AbsoluteX}, {LSR, AbsoluteX}, {SRE, AbsoluteX},
    {RTS, Implicit}, {ADC, IndirectX}, {NOP, None}, {RRA, IndirectX}, {NOP, ZeroPage}, {ADC, ZeroPage}, {ROR, ZeroPage}, {RRA, ZeroPage}, {PLA, Implicit}, {ADC, Immediate}, {ROR, Immediate}, {ARR, Immediate}, {JMP, Indirect}, {ADC, Absolute}, {ROR, Absolute}, {RRA, Absolute},
    {BVS, Relative}, {ADC, IndirectY}, {NOP, None}, {RRA, IndirectY}, {NOP, ZeroPageX}, {ADC, ZeroPageX}, {ROR, ZeroPageX}, {RRA, ZeroPageX}, {SEI, Implicit}, {ADC, AbsoluteY}, {NOP, Implicit}, {RRA, AbsoluteY}, {NOP, AbsoluteX}, {ADC, AbsoluteX}, {ROR, AbsoluteX}, {RRA, AbsoluteX},
    {NOP, Immediate}, {STA, IndirectX}, {NOP, Immediate}, {SAX, IndirectX}, {STY, ZeroPage}, {STA, ZeroPage}, {STX, ZeroPage}, {SAX, ZeroPage}, {DEY, Implicit}, {NOP, Immediate}, {TXA, Immediate}, {NOP, Implicit}, {STY, Absolute}, {STA, Absolute}, {STX, Absolute}, {SAX, Absolute},
    {BCC, Relative}, {STA, IndirectY}, {NOP, None}, {NOP, IndirectY}, {STY, ZeroPageX}, {STA, ZeroPageX}, {STX, ZeroPageY}, {SAX, ZeroPageY}, {TYA, Implicit}, {STA, AbsoluteY}, {TXS, Implicit}, {NOP, AbsoluteY}, {NOP, AbsoluteX}, {STA, AbsoluteX}, {NOP, AbsoluteY}, {NOP, AbsoluteY},
    {LDY, Immediate}, {LDA, IndirectX}, {LDX, Immediate}, {LAX, IndirectX}, {LDY, ZeroPage}, {LDA, ZeroPage}, {LDX, ZeroPage}, {LAX, ZeroPage}, {TAY, Implicit}, {LDA, Immediate}, {TAX, Implicit}, {LAX, Immediate}, {LDY, Absolute}, {LDA, Absolute}, {LDX, Absolute}, {LAX, Absolute},
    {BCS, Relative}, {LDA, IndirectY}, {NOP, None}, {LAX, IndirectY}, {LDY, ZeroPageX}, {LDA, ZeroPageX}, {LDX, ZeroPageY}, {LAX, ZeroPageY}, {CLV, Implicit}, {LDA, AbsoluteY}, {TSX, Implicit}, {LAS, AbsoluteY}, {LDY, AbsoluteX}, {LDA, AbsoluteX}, {LDX, AbsoluteY}, {LAX, AbsoluteY},
    {CPY, Immediate}, {CMP, IndirectX}, {NOP, Immediate}, {DCP, IndirectX}, {CPY, ZeroPage}, {CMP, ZeroPage}, {DEC, ZeroPage}, {DCP, ZeroPage}, {IndirectY, Implicit}, {CMP, Immediate}, {DEX, Implicit}, {AXS, Immediate}, {CPY, Absolute}, {CMP, Absolute}, {DEC, Absolute}, {DCP, Absolute},
    {BNE, Relative}, {CMP, IndirectY}, {NOP, None}, {DCP, IndirectY}, {NOP, ZeroPageX}, {CMP, ZeroPageX}, {DEC, ZeroPageX}, {DCP, ZeroPageX}, {CLD, Implicit}, {CMP, AbsoluteY}, {NOP, Implicit}, {DCP, AbsoluteY}, {NOP, AbsoluteX}, {CMP, AbsoluteX}, {DEC, AbsoluteX}, {DCP, AbsoluteX},
    {CPX, Immediate}, {SBC, IndirectX}, {NOP, Immediate}, {ISC, IndirectX}, {CPX, ZeroPage}, {SBC, ZeroPage}, {INC, ZeroPage}, {ISC, ZeroPage}, {INX, Implicit}, {SBC, Immediate}, {NOP, Implicit}, {SBC, Immediate}, {CPX, Absolute}, {SBC, Absolute}, {INC, Absolute}, {ISC, Absolute},
    {BEQ, Relative}, {SBC, IndirectY}, {NOP, None}, {ISC, IndirectY}, {NOP, ZeroPageX}, {SBC, ZeroPageX}, {INC, ZeroPageX}, {ISC, ZeroPageX}, {SED, Implicit}, {SBC, AbsoluteY}, {NOP, Immediate}, {ISC, AbsoluteY}, {NOP, AbsoluteX}, {SBC, AbsoluteX}, {INC, AbsoluteX}, {ISC, AbsoluteX}
}

const uint8_t InstructionCycles[256] = {
// HI/LO 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
// -------------------------------------------------------
/* 0 */  7, 6, 0, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
/* 1 */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
/* 2 */  6, 6, 0, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
/* 3 */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
/* 4 */  6, 6, 0, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
/* 5 */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
/* 6 */  6, 6, 0, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
/* 7 */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
/* 8 */  2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
/* 9 */  2, 6, 0, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
/* A */  2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
/* B */  2, 5, 0, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
/* C */  2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
/* D */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
/* E */  2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
/* F */  2, 5, 0, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
};


/*
 * 7 different flags for CPU flag to display current status
 * */
typedef enum {
    Carry = 0,
    Zero = 1 << 1,
    Interrupt = 1 << 2,
    Decimal = 1 << 3,
    Break = 1 << 4,
    Unused  = 1 << 5,
    Overflow = 1 << 6,
    Negative = 1 << 7
} ProcessorFlag;


/*
 * 6502 CPU has five 8-bit registers and one 16-bit register (Program Counter)
 *
 * https://www.nesdev.org/wiki/Programming_Basics
 * */
typedef struct {
    // Used to perform arithmetic operations
    uint8_t Accumulator;    // Used to read/write to memory and store arithmetic/logic results
    uint8_t XIndex;     // Used for several addressing modes
    uint8_t YIndex;     // Used for several addressing modes.
    // Other
    uint8_t Flag;   // Represented as 7 different flags to show the status of the processor
    ProcessorFlag StackPointer;   // Holds the address to the current location on the stack
    uint16_t ProgramCounter;    // Keeps track of the memory address of the next instruction to be executed
} Registers;


// The actual CPU
typedef struct {
    Registers registers;
    struct Bus *bus;
    uint64_t cycles;    // Cycle counter
    uint8_t current_value;      // Current opcode
} CPU;


void CpuInit(CPU *cpu);
void CpuWrite(CPU *cpu, uint16_t address, uint8_t value);    // Write memory
uint8_t CpuRead(CPU *cpu, uint16_t address);     // Read memory
void CpuConnectToBus(CPU *cpu, Bus *bus);    // Connect CPU to bus
void CpuReset(CPU *cpu);
void CpuStep(CPU *cpu);    // Perform one clock cycle and execute an instruction
void CpuNmi(CPU *cpu);     // Non maskable interrupt 
    
// Addressing modes functions
void IMP(CPU *cpu);     // Implicit
void ACC(CPU *cpu);     // Accumulator
void IMM(CPU *cpu);     // Immediate
void ZPO(CPU *cpu);     // Zero Page
void ZPX(CPU *cpu);     // Zero Page X
void ZPY(CPU *cpu);     // Zero Page Y
void REL(CPU *cpu);     // Relative
void ABS(CPU *cpu);     // Absolute
void ABX(CPU *cpu);     // Absolute X
void ABY(CPU *cpu);     // Absolute Y
void IND(CPU *cpu);     // Indirect
void IDX(CPU *cpu);     // Indirect X
void IDY(CPU *cpu);     // Indirect Y



void ADC();     // Add with carry
void AND();     // Logical And (And With Accumulator)
void ASL();     // Arithmetic Shift Left
void BCC();     // Branch if Carry Clear
void BCS();     // Branch if Carry Set
void BEQ();     // Branch if Equal
void BIT();     // Bit Test
void BMI();     // Branch if Minus
void BNE();     // Branch if Not Equal
void BPL();     // Branch if Positive
void BRK();     // Force Interrupt
void BVC();     // Branch if Overflow Clear
void BVS();     // Branch if Overflow Set
void CLC();     // Clear Carry Flag
void CLD();     // Clear Decimal Mode
void CLI();     // Clear Interrupt Disable
void CLV();     // Clear Overflow Flag
void CMP();     // Compare
void CPX();     // Compare X Register
void CPY();     // Compare Y Register
void DEC();     // Decrement Memory
void DEX();     // Decrement X Register
void DEY();     // Decrement Y Register
void EOR();     // Exclusive OR
void INC();     // Increment Memory
void INX();     // Increment X Register
void INY();     // Increment Y Register
void JMP();     // Jump
void JSR();     // Jump to Subroutine
void LDA();     // Load Accumulator
void LDX();     // Load X Register
void LDY();     // Load Y Register
void LSR();     // Logical Shift Right
void NOP();     // No Operation
void ORA();     // Logical Inclusive Or
void PHA();     // Push Accumulator
void PHP();     // Push Processor Status
void PLA();     // Pull Accumulator
void PLP();     // Pull Processor Status
void ROL();     // Rotate Left
void ROR();     // Rotate Right
void RTI();     // Return from Interrupt
void RTS();     // Return from Subroutine
void SBC();     // Subtract with Carry
void SEC();     // Set Carry Flag
void SED();     // Set Decimal Flag
void SEI();     // Set Interrupt Flag
void STA();     // Store Accumulator
void STX();     // Store X Register
void STY();     // Store Y Register
void TAX();     // Transfer Accumulator to X
void TAY();     // Transfer Accumulator to Y
void TSX();     // Transfer Stack Pointer to X
void TXA();     // Transfer X to Accumulator
void TXS();     // Transfer X to Stack Pointer
void TYA();     // Transfer X to Accumulators

#endif