//ROM.h


#ifndef ROM_H
#define ROM_H

#include <stdint.h>
#include <stdio.h>

#define ROM_OFFSET 0x0100

typedef struct GBHeader{
    char title[17];          // 0x0134–0x0143
    uint8_t cgb_flag;        // 0x0143
    uint8_t sgb_flag;        // 0x0146
    uint8_t cartridge_type;  // 0x0147
    uint8_t rom_size;        // 0x0148
    uint8_t ram_size;        // 0x0149
    uint8_t destination;     // 0x014A
    uint8_t old_license;     // 0x014B
    uint8_t rom_version;     // 0x014C
    uint8_t header_checksum; // 0x014D
    uint16_t global_checksum;// 0x014E–0x014F
} GBHeader;

uint8_t* read_rom(const char* filename, size_t* size);
void parse_rom_header(const uint8_t* rom, GBHeader* header);
void print_header_info(struct GBHeader *header);
const char* cart_type_string(uint8_t type);
const char* ROM_Size_string(uint8_t type);
const char* RAM_Size_string(uint8_t type);

#endif // ROM_H