// /*
//  * The bus is a communication system that sends control signals and data between the processor and other components.
//  * The main purpose for the bus will be to read and write.
//  * */

// #include "bus.h"

// Bus::Bus() {

// }

// Bus::~Bus() {

// }

// void Bus::Write(uint16_t address, uint8_t value) {
//     if (address >= 0x0000 && address <= 0xffff) {
//         ram[address] = value;
//     }
// }

// uint8_t Bus::Read(uint16_t address, bool ReadOnly) {
//     if (address >= 0x0000 && address <= 0xffff) {
//         return ram[address];
//     }
//     return 0x00;
// }


