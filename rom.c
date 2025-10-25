//ROM.c
//10/19/25

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rom.h"

uint8_t* read_rom(const char* filename, size_t* size){
    FILE *fptr = fopen(filename, "rb");
    if(!fptr){
        printf("Error opening file\n");
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    *size = ftell(fptr);
    rewind(fptr);

    uint8_t* buffer = malloc(*size);
    if (!buffer) {
        perror("Failed to allocate memory for ROM");
        fclose(fptr);
        return NULL;
    }

    if(fread(buffer, 1, *size, fptr) != *size){
        perror("Failed to read entire ROM");
        free(buffer);
        fclose(fptr);
        return NULL;
    }

    fclose(fptr);
    return buffer;
}

void parse_rom_header(const uint8_t* rom, GBHeader* header){
    memcpy(header->title, &rom[0x0134], 16);
    header->title[16] = '\0';
    header->cgb_flag = rom[0x0143];
    header->sgb_flag = rom[0x0146];
    header->cartridge_type = rom[0x0147];
    header->rom_size = rom[0x0148];
    header->ram_size = rom[0x0149];
    header->destination = rom[0x014A];
    header->old_license = rom[0x014B];
    header->rom_version = rom[0x014C];
    header->header_checksum = rom[0x014D];
    header->global_checksum = (rom[0x014E] << 8) | rom[0x014F];

}
void print_header_info(struct GBHeader *header){
    printf("Title: %s\n", header->title);
    printf("Cartridge Type: %s\n",cart_type_string(header->cartridge_type));
    printf("ROM Size: %s\n",ROM_Size_string(header->rom_size));
    printf("RAM Size: %s\n",RAM_Size_string(header->ram_size));

}
const char* cart_type_string(uint8_t type) {
    switch(type) {
        case 0x00: return "ROM ONLY";
        case 0x01: return "MBC1";
        case 0x02: return "MBC1+RAM";
        case 0x03: return "MBC1+RAM+BATTERY";
        case 0x05: return "MBC2";
        case 0x06: return "MBC2+BATTERY";
        case 0x08: return "ROM+RAM";
        case 0x09: return "ROM+RAM+BATTERY";
        case 0x0B: return "MMM01";
        case 0x0C: return "MMM01+RAM";
        case 0x0D: return "MMM01+RAM+BATTERY";
        case 0x0F: return "MBC3+TIMER+BATTERY";
        case 0x10: return "MBC3+TIMER+RAM+BATTERY";
        case 0x11: return "MBC3";
        case 0x12: return "MBC3+RAM";
        case 0x13: return "MBC3+RAM+BATTERY";
        case 0x19: return "MBC5";
        case 0x1A: return "MBC5+RAM";
        case 0x1B: return "MBC5+RAM+BATTERY";
        case 0x1C: return "MBC5+RUMBLE";
        case 0x1D: return "MBC5+RUMBLE+RAM";
        case 0x1E: return "MBC5+RUMBLE+RAM+BATTERY";
        case 0x20: return "MBC6";
        case 0x22: return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case 0xFC: return "POCKET CAMERA";
        case 0xFD: return "BANDAI TAMA5";
        case 0xFE: return "HuC3";
        case 0xFF: return "HuC1+RAM+BATTERY";
        default: return "Unknown";
    }
}

const char* ROM_Size_string(uint8_t type) {
    switch(type) {
        case 0x00: return "32 KiB";
        case 0x01: return "64 KiB";
        case 0x02: return "128 KiB";
        case 0x03: return "256 KiB";
        case 0x04: return "512 KiB";
        case 0x05: return "1 MiB";
        case 0x06: return "2 MiB";
        case 0x07: return "4 MiB";
        case 0x08: return "8 MiB";
        default: return "Unknown";
    }
}

const char* RAM_Size_string(uint8_t type) {
    switch(type) {
        case 0x00: return "0 KiB";
        case 0x02: return "8 KiB";
        case 0x03: return "32 KiB";
        case 0x04: return "128 KiB";
        case 0x05: return "64 KiB";
        default: return "Unknown";
    }
}