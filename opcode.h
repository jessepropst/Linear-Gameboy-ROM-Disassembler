//opcode_table.h
//10/18/25

// include/opcode.h
#ifndef OPCODE_H
#define OPCODE_H

#include <stdint.h>
#include "opcode.h"

typedef struct {
    const char *mnemonic;     // Instruction name, e.g., "LD", "JP", "ADD"
    const char *operand_fmt;  // Operand format, e.g., "A,B" or "(HL+),A"
    uint8_t length;           // Total instruction length in bytes (1–3)
    uint8_t cycles;           // Clock cycles (main timing)
    uint8_t alt_cycles;       // Alternate cycles (e.g. conditional jump taken)
} Opcode;

extern const Opcode opcode_table[256];
extern const Opcode cb_table[256]; // for CB-prefixed opcodes

#endif
