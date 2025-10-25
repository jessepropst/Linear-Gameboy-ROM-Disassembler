//main.c

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "rom.h"
#include "disassembler.h"
#include "opcode.h"

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Enter in a file name. \n");
        return -1;
    } else {
        const char* filename = argv[1];

        size_t size;
        uint8_t* buffer = read_rom(filename, &size);

        if (!buffer) {
            printf("Unable to read file.\n");
            return -1;
        }

        GBHeader header;
        parse_rom_header(buffer, &header);
        print_header_info(&header);

        disassemble(buffer, size);

        free(buffer);
        return 0;
    }
}