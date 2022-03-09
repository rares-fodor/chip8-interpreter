#ifndef CHIP_8_H
#define CHIP_8_H

#include <stdint.h>

#define MEM_SIZE 4069
#define REG_COUNT 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16
#define DISP_WIDTH  64
#define DISP_HEIGHT 32
#define FONT_SIZE 80

// Every character in the fontset has a size of 5 bytes
#define FONT_CHARACTER_SIZE 5

#define PC_START_ADDR   0x200
#define START_ADDR      0x200
#define END_ADDR        0xFFF
#define FONT_START_ADDR 0x000

typedef struct {
    uint8_t mem[MEM_SIZE];
    uint8_t reg[REG_COUNT];
    uint8_t keypad[KEYPAD_SIZE];
    uint16_t stack[STACK_SIZE];
    uint32_t display_mem[DISP_HEIGHT * DISP_WIDTH];

    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t index;
    uint16_t pc;

    uint16_t opcode;
} chip8;

void init_chip8(chip8 *chip8);
void load_rom(chip8 *chip8, const char* filename);
void instruction_fetch(chip8 *chip8);
void execute(chip8 *chip8);
void cycle(chip8 *chip8);

#endif // CHIP_8_H
