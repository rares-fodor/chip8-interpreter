#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "chip8.h"

void error_handle(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void load_rom(chip8* chip8, const char *filename) {
    FILE *rom = NULL;
    uint8_t *buff;
    long filesize;

    rom = fopen(filename, "rb");    
    if (!rom) { error_handle("Couln't read ROM"); }

    // Get filesize
    fseek(rom, 0, SEEK_END);
    filesize = ftell(rom);
    rewind(rom);

    buff = (uint8_t *) malloc(sizeof(uint8_t) * filesize);
    if (!buff) { error_handle("Failed to allocate memory for ROM buffer"); }

    // Read ROM file into buffer
    fread(buff, sizeof(uint8_t), filesize, rom);
    if ((END_ADDR - START_ADDR) < filesize) { error_handle("Not enough memory for ROM!"); }

    // Copy bytes from buffer into memory
    for (size_t i = 0; i < filesize; ++i) {
        chip8->mem[i + START_ADDR] = buff[i];
    }

    free(buff);
}
