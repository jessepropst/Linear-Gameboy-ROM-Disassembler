//Disassembler.c

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "opcode.h"

uint16_t pc = 0x150;

//prototypes
void printOperand(uint8_t byte, uint8_t operand, Opcode opcode, const uint8_t *rom);
void handleJR(uint8_t byte, int8_t offset);

void disassemble(const uint8_t *rom, size_t rom_size){
    //PC - Program Counter
       //Start after header
    while (pc < rom_size){
        //Print current position
        printf("%04X: ", pc);
        
        //get the byte of data
        uint8_t byte = rom[pc];

        if(byte == 0xCB){
            if(pc + 2 > rom_size){
                printf("Truncated instruction at end of ROM\n");
                break;
            }

            //handle CB opcodes
            byte = rom[pc+1];
            Opcode CB = cb_table[byte];

            for (int i = 0; i < CB.length; i++) {
                printf("%02X ", rom[pc + i]);
            }
            for (int i = CB.length; i < 3; i++) {
                printf("   "); // pad up to 3 bytes
            }

            //Handle CB opcode
            printf("%s %s", CB.mnemonic, CB.operand_fmt);

            pc += CB.length;
            printf("\n");
        } else {
            Opcode opcode = opcode_table[byte];
        
            //Check the instruction is valid
            if(opcode.cycles == 0){
                printf("%s\n", "Unknown Opcode");
        
            //Handle valid instructions
            } else if (opcode.length == 1){
                for (int i = 0; i < opcode.length; i++) {
                    printf("%02X ", rom[pc + i]);
                }
                for (int i = opcode.length; i < 3; i++) {
                    printf("   "); // pad up to 3 bytes
                }

                //Handle 1 byte opcode
                printf("%s ", opcode.mnemonic);

                //Check for operand
                if(opcode.operand_fmt[0] != '\0'){
                    printf("%s", opcode.operand_fmt);
                }
            } else if (opcode.length == 2){
                if(pc + opcode.length > rom_size){
                    printf("Truncated instruction at end of ROM\n");
                    break;
                }

                for (int i = 0; i < opcode.length; i++) {
                    printf("%02X ", rom[pc + i]);
                }
                for (int i = opcode.length; i < 3; i++) {
                    printf("   "); // pad up to 3 bytes
                }

                //Handle 2 byte opcode
                printf("%s ", opcode.mnemonic);

                //Check for operand
                if(opcode.operand_fmt[0] != '\0'){

                    uint8_t operand = rom[pc + 1];
                    printOperand(byte, operand, opcode, rom);
                
                }

            } else {
                if(pc + opcode.length > rom_size){
                    printf("Truncated instruction at end of ROM\n");
                    break;
                }

                for (int i = 0; i < opcode.length; i++) {
                    printf("%02X ", rom[pc + i]);
                }
                for (int i = opcode.length; i < 3; i++) {
                    printf("   "); // pad up to 3 bytes
                }

                //Handle 3 byte opcode
                printf("%s ", opcode.mnemonic);

                //Check for operand
                if(opcode.operand_fmt[0] != '\0'){

                    uint8_t operand = rom[pc + 1];
                    printOperand(byte, operand, opcode, rom);
                }
            }
            pc += opcode.length;
            printf("\n");
        }
        
    }
}

void printOperand(uint8_t byte, uint8_t operand,Opcode opcode, const uint8_t *rom){
    if (byte == 0xE0) {       // LDH ($nn),A
        printf("($%02X),A", operand);
    } else if (byte == 0xF0) { // LDH A,($nn)
        printf("A,($%02X)", operand);
        //Check for immeadiate
    } else if (byte == 0x01){
        uint16_t imm16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("BC,#%04X", imm16);
    } else if (byte == 0x06){
        printf("B,#%02X", operand);
    } else if (byte == 0x08){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("($%04X),SP", address16);
    } else if (byte == 0x0E){
        printf("C,#%02X", operand);
    } else if (byte == 0x11){
        uint16_t imm16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("DE,#%04X", imm16);
    } else if (byte == 0x16){
        printf("D,#%02X", operand);
    } else if (byte == 0x1E){
        printf("E,#%02X", operand);
    } else if (byte == 0x20){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("NZ,%+d -> $%04X", offset, pc + 2 + offset);
    } else if (byte == 0x21){
        uint16_t imm16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("HL,#%04X", imm16);
    } else if (byte == 0x26){
        printf("H,#%02X", operand);
    } else if (byte == 0x28){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("Z,%+d -> $%04X", offset, pc + 2 + offset);
    } else if (byte == 0x2E){
        printf("L,#%02X", operand);
    } else if (byte == 0x30){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("NC,%+d -> $%04X", offset, pc + 2 + offset);
    } else if (byte == 0x31){
        uint16_t imm16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("SP,#%04X", imm16);
    } else if (byte == 0x36){
        printf("(HL),#%02X", operand);
    } else if (byte == 0x38){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("C,%+d -> $%04X", offset, pc + 2 + offset);
    } else if (byte == 0x3E){
        printf("A,#%02X", operand);
    } else if (byte == 0xC2 || byte == 0xC4){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("NZ,$%04X", address16);
    } else if (byte == 0xC6){
        printf("A,#%02X", operand);
    } else if (byte == 0xCA || byte == 0xCC){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("Z,$%04X", address16);
    } else if (byte == 0xCE){
        printf("A,#%02X", operand);
    } else if (byte == 0xD2 || byte == 0xD4){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("NC,$%04X", address16);
    } else if (byte == 0xDA || byte == 0xDC){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("C,$%04X", address16);
    } else if (byte == 0xDE){
        printf("A,#%02X", operand);
    } else if (byte == 0xE8){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("SP,%+d", offset);
    } else if (byte == 0xEA){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("($%04X),A", address16);
    } else if (byte == 0xF8){
        int8_t offset = (int8_t)rom[pc + 1];
        printf("HL,SP,%+d", offset);
    } else if (byte == 0xFA){
        uint16_t address16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("A,($%04X)", address16);
    } else if (strstr(opcode.operand_fmt, "d8") != NULL){
        uint8_t imm8 = rom[pc + 1];  // fetch next byte
        printf("#%02X", imm8);
    } else if (strstr(opcode.operand_fmt, "d16") != NULL){
        uint16_t imm16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("$%04X", imm16);
    } else if(strstr(opcode.operand_fmt, "a8") != NULL){
        uint8_t addr8 = rom[pc + 1];
        printf("$%02X", addr8);
    } else if (strstr(opcode.operand_fmt, "a16") != NULL){
        uint16_t addr16 = rom[pc + 1] | (rom[pc + 2] << 8);
        printf("$%04X", addr16);
    } else if(strstr(opcode.operand_fmt, "r8") != NULL){
        int8_t offset = rom[pc+1];
        printf("%+d -> $%04X", offset, pc + 2 + offset);
    } else {
        uint8_t operand = rom[pc+1];
        printf("%02X", operand); // normal hex
    }
}