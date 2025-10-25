//Disassembler.h

#include <stdint.h>
#include "opcode.h"

void disassemble(const uint8_t *rom, size_t rom_size);
void printOperand(uint8_t byte, uint8_t operand,Opcode opcode, const uint8_t *rom);