#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "instructions.h"
#include "chip8.h"

// Clear display
void OP_0x00E0 (chip8 *chip8) {
    memset(chip8->display_mem, 0, sizeof(chip8->display_mem));
}

// Return from subroutine
void OP_0x00EE (chip8 *chip8) {
    chip8->sp--;
    chip8->pc = chip8->stack[chip8->sp];
}

// Jump to addr NNN
void OP_0x1NNN (chip8 *chip8) {
    chip8->pc = (chip8->opcode & 0x0FFF);
}

// Execute subroutine starting at addr NNN (Call)
void OP_0x2NNN (chip8 *chip8) {
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->sp++;
    chip8->pc = chip8->opcode & 0x0FFF;
}

// If value of Vx is NN, skip next instruction
void OP_0x3XNN (chip8 *chip8) {
    uint8_t x  = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;
    if (chip8->reg[x] == nn) {
        chip8->pc += 2;
    }
}

// If value of Vx is NOT NN, skip next instruction
void OP_0x4XNN (chip8 *chip8) {
    uint8_t x  = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;
    if (chip8->reg[x] != nn) {
        chip8->pc += 2;
    }
}

// If value of Vx is equal to value of Vy, skip next instruction
void OP_0x5XY0 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->reg[x] == chip8->reg[y]) {
        chip8->pc += 2;
    }
}

// Store NN into Vx
void OP_0x6XNN (chip8 *chip8) {
    uint8_t x  = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;
    chip8->reg[x] = nn;
}

void OP_0x7XNN (chip8 *chip8) {
    uint8_t x  = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;
    chip8->reg[x] += nn;
}

void OP_0x8XY0 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] = chip8->reg[y];
}

void OP_0x8XY1 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] |= chip8->reg[y];
}

void OP_0x8XY2 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] &= chip8->reg[y];
}

void OP_0x8XY3 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] ^= chip8->reg[y];
}

void OP_0x8XY4 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;

    int sum = chip8->reg[x] + chip8->reg[y];
    chip8->reg[x] += chip8->reg[y];

    if (sum > 255) {
        chip8->reg[0xF] = 1;
    } else {
        chip8->reg[0xF] = 0;
    }
}

void OP_0x8XY5 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] -= chip8->reg[y];

    if (chip8->reg[x] > chip8->reg[y]) {
        chip8->reg[0xF] = 1;
    } else {
        chip8->reg[0xF] = 0;
    }
}

void OP_0x8XY6 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[0xF] = chip8->reg[y] & 0x01;
    chip8->reg[x] = chip8->reg[y] >> 1;
}

void OP_0x8XY7 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[x] = chip8->reg[y] - chip8->reg[x];
    
    if (chip8->reg[y] > chip8->reg[x]) {
        chip8->reg[0xF] = 1;
    } else {
        chip8->reg[0xF] = 0;
    }
}

void OP_0x8XYE (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    chip8->reg[0xF] = chip8->reg[y] & 0x80;
    chip8->reg[x] = chip8->reg[y] << 1;
}

void OP_0x9XY0 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->reg[x] != chip8->reg[y]) {
        chip8->pc += 2;
    }

}


void OP_0xANNN (chip8 *chip8) {
    uint8_t nn = chip8->opcode & 0x0FFF;
    chip8->index = nn; 
}

void OP_0xBNNN (chip8 *chip8) {
    uint8_t nn = chip8->opcode & 0x0FFF;
    chip8->pc = nn + chip8->reg[0];
}

void OP_0xCXNN (chip8 *chip8) {
    uint8_t x  = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;
    chip8->reg[x] = (rand() % 255) & nn;
}

// TODO!!!!!!
void OP_0xDXYN (chip8 *chip8) {
    // draw
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    uint8_t n = chip8->opcode & 0x000F;
    uint16_t index = chip8->index;

    // Position to draw at !!!!!!
    uint8_t pos_x = chip8->reg[x] % DISP_WIDTH; 
    uint8_t pos_y = chip8->reg[y] % DISP_HEIGHT;

    for (size_t i = 0; i < n; ++i) {
        // Read n bytes from memory
        uint8_t sprite_byte = chip8->mem[index + i];
        for (size_t j = 0; j < 8; ++j) {
            uint8_t sprite_pixel = sprite_byte & (0x80 >> j);
            uint32_t *display_pixel = &chip8->display_mem[(pos_y + i) * DISP_WIDTH +
                                                          (pos_x + j) * DISP_HEIGHT];
            if (sprite_pixel) {
                if (*display_pixel == 0xFFFFFFFF) chip8->reg[0xF] = 1;
                *display_pixel ^= 0xFFFFFFFF;
            }

        }
    }
}

void OP_0xEX9E (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (chip8->keypad[chip8->reg[x]])
        chip8->pc += 2;
}

void OP_0xEXA1 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (!chip8->keypad[chip8->reg[x]])
        chip8->pc += 2;
}

void OP_0xFX07 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->reg[x] = chip8->delay_timer;
}

void OP_0xFX0A (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    if (1) {

    } else {
        // Repeat instruction until key is pressed 
        chip8->pc -= 2;
    }
}

void OP_0xFX15 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->delay_timer = chip8->reg[x];
}
void OP_0xFX18 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->sound_timer = chip8->reg[x];
}
void OP_0xFX1E (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    chip8->index += chip8->reg[x];
}

void OP_0xFX29 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t digit = chip8->reg[x];
    chip8->index = FONT_START_ADDR + (digit * FONT_CHARACTER_SIZE);
}

void OP_0xFX33 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t index = chip8->index;
    uint8_t value = chip8->reg[x];

    chip8->mem[index + 2] = value % 10;
    value /= 10;
    chip8->mem[index + 1] = value % 10;
    value /= 10;
    chip8->mem[index] = value;
}

void OP_0xFX55 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    for (size_t i = 0; i <= x; ++i) {
        chip8->mem[chip8->index + i] = chip8->reg[i]; 
    }
    chip8->index = chip8->index + x + 1;
}

void OP_0xFX65 (chip8 *chip8) {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    for (size_t i = 0; i <= x; ++i) {
        chip8->reg[i] = chip8->mem[chip8->index + i]; 
    }
    chip8->index = chip8->index + x + 1;
}
