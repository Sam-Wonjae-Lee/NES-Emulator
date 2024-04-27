/*
 * The cpu used in the NES is known as the Ricoh 2A03 which is based on the MOS Technology 6502 processor.
 * The cpu is the main processor chip and contains information on addressing modes, registers, and opcodes.
 * */

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
    Carry = 0,
    Zero = 1 << 1,
    Interrupt = 1 << 2,
    Decimal = 1 << 3,
    Break = 1 << 4,
    Unused  = 1 << 5,
    Overflow = 1 << 6,
    Negative = 1 << 7
};

/*
 * 6502 CPU has five 8-bit registers and one 16-bit register (Program Counter)
 *
 * https://www.nesdev.org/wiki/Programming_Basics
 * */
struct Register {
    // Arithmetic
    uint8_t Accumulator;    // Used to read/write to memory and store arithmetic/logic results
    uint8_t XIndex;     // Used for several addressing modes
    uint8_t YIndex;     // Used for several addressing modes.
    // Other
    uint8_t Flag;   // Represented as 7 different flags to show the status of the processor
    uint8_t StackPointer;   // Holds the address to the current location on the stack
    uint16_t ProgramCounter;    // Keeps track of the memory address of the next instruction to be executed
};

class Bus;

class CPU {
public:
    AddressingMode CpuAddressingMode;
    ProcessorFlag CpuProcessorFlag;
    Register CpuRegister;

    Bus *bus;
    uint8_t cycles;

    void Write(uint16_t address, uint8_t value);
    uint8_t Read(uint16_t address);
    void ConnectToBus(Bus *bus);    // Connect CPU to bus
    void Reset();
    void Step();    // Perform one clock cycle


    // Addressing modes functions
    void Implicit();
    void Accumulator();
    void Immediate();
    void ZeroPage();
    void ZeroPageX();
    void ZeroPageY();
    void Relative();
    void Absolute();
    void AbsoluteX();
    void AbsoluteY();
    void Indirect();
    void IndirectX();
    void IndirectY();

    // Opcodes functions
    // https://www.oxyron.de/html/opcodes02.html
    // https://www.nesdev.org/obelisk-6502-guide/reference.html
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
};

