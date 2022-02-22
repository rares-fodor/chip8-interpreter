#ifndef CHIP_8_H
#define CHIP_8_H

#include <stdint.h>

#define START_ADDR 0x200
#define END_ADDR   0xFFF

typedef struct {
    uint8_t mem[4096];
    uint8_t reg[16];
    uint8_t stack[16];
    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t index;
    uint16_t pc;

} chip8;

void load_rom(chip8 *chip8, const char* filename);

#endif // CHIP_8_H
