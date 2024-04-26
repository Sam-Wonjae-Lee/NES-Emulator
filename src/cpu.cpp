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


