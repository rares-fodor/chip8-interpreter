#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "chip8.h"

void error_handle(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void init_chip8(chip8 *chip8) {
    srand(time(NULL));   

    chip8->sp = 0;
    chip8->index = 0;
    chip8->pc = PC_START_ADDR;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->opcode = 0;

    memset(chip8->display_mem, 0, sizeof(chip8->display_mem));
    memset(chip8->mem,   0, sizeof(chip8->mem));
    memset(chip8->stack, 0, sizeof(chip8->stack));
    memset(chip8->reg,   0, sizeof(chip8->reg));
    memset(chip8->keypad, 0, sizeof(chip8->keypad));

    // Load fonts into memory starting at 0x000
    uint8_t font_sprites[FONT_SIZE] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	    0x20, 0x60, 0x20, 0x20, 0x70, // 1
	    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    for (size_t i = FONT_START_ADDR; i < FONT_SIZE; ++i) {
        chip8->mem[i] = font_sprites[i];
    }

}

void load_rom(chip8 *chip8, const char *filename) {
    FILE *rom = NULL;
    uint8_t *buff;
    long filesize;

    rom = fopen(filename, "rb");    
    if (!rom) { error_handle("Couldn't read ROM"); }

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

void instruction_fetch(chip8 *chip8) { 
    uint8_t high = chip8->mem[chip8->pc];
    uint8_t low  = chip8->mem[chip8->pc + 1];
    chip8->opcode = low << 8 | high;
}

void execute(chip8 *chip8) {
    uint16_t opcode = chip8->opcode;
    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x00FF) {
                case 0x00E0:
                    // Clear the screen
                    break;
                case 0x00EE:
                    // Return from a subroutine
                    break;
                default:
                    error_handle("Unrecognized opcode");
            }
            break;
        case 0x1000:
            // Jump to address
            break;
        case 0x2000:
            // Execute subroutine starting at address NNN
            break;
        case 0x3000:
            break;
        case 0x4000:
            break;
        case 0x5000:
            break;
        case 0x6000:
            break;
        case 0x7000:
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    break;
                case 0x0001:
                    break;
                case 0x0002:
                    break;
                case 0x0003:
                    break;
                case 0x0004:
                    break;
                case 0x0005:
                    break;
                case 0x0006:
                    break;
                case 0x0007:
                    break;
                case 0x000E:
                    break;
                default:
                    error_handle("Unrecognized opcode");
            }
            break;
        case 0x9000:
            break;
        case 0xA000:
            break;
        case 0xB000:
            break;
        case 0xC000:
            break;
        case 0xD000:
            break;
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    break;
                case 0x00A1:
                    break;
                default:
                    error_handle("Unrecognized opcode");
            }
            break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    break;
                case 0x000A:
                    break;
                case 0x0015:
                    break;
                case 0x0018:
                    break;
                case 0x001E:
                    break;
                case 0x0029:
                    break;
                case 0x0033:
                    break;
                case 0x0055:
                    break;
                case 0x0065:
                    break;
                default:
                    error_handle("Unrecognized opcode");
            }
            break;
        default:
            error_handle("Unrecognized opcode");
    }
}

void cycle(chip8 *chip8) {
    instruction_fetch(chip8);
    chip8->pc += 2;
    execute(chip8);
}
