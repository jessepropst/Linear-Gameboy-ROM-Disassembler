//ROM.h
//10/18/25
//Loop through ROM data
//Decode bytes using a lookup table (opcode_table.h)
//Print mnemonics (like LD A,B or JP 0x1234)

#include <stdint.h>
#include "opcode.h"

void disassemble(const uint8_t *rom, size_t rom_size);
void printOperand(uint8_t byte, uint8_t operand,Opcode opcode, const uint8_t *rom);