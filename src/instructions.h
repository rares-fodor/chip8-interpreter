#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

void OP_0x00E0 (chip8 *chip8);
void OP_0x00EE (chip8 *chip8);
void OP_0x1NNN (chip8 *chip8);
void OP_0x2NNN (chip8 *chip8);
void OP_0x3XNN (chip8 *chip8);
void OP_0x4XNN (chip8 *chip8);
void OP_0x5XY0 (chip8 *chip8);
void OP_0x6XNN (chip8 *chip8);
void OP_0x7XNN (chip8 *chip8);
void OP_0x8XY0 (chip8 *chip8);
void OP_0x8XY1 (chip8 *chip8);
void OP_0x8XY2 (chip8 *chip8);
void OP_0x8XY3 (chip8 *chip8);
void OP_0x8XY4 (chip8 *chip8);
void OP_0x8XY5 (chip8 *chip8);
void OP_0x8XY6 (chip8 *chip8);
void OP_0x8XY7 (chip8 *chip8);
void OP_0x8XYE (chip8 *chip8);
void OP_0x9XY0 (chip8 *chip8);
void OP_0xANNN (chip8 *chip8);
void OP_0xBNNN (chip8 *chip8);
void OP_0xCXNN (chip8 *chip8);
void OP_0xDXYN (chip8 *chip8);
void OP_0xEX9E (chip8 *chip8);
void OP_0xEXA1 (chip8 *chip8);
void OP_0xFX07 (chip8 *chip8);
void OP_0xFX0A (chip8 *chip8);
void OP_0xFX15 (chip8 *chip8);
void OP_0xFX18 (chip8 *chip8);
void OP_0xFX1E (chip8 *chip8);
void OP_0xFX29 (chip8 *chip8);
void OP_0xFX33 (chip8 *chip8);
void OP_0xFX55 (chip8 *chip8);
void OP_0xFX65 (chip8 *chip8);

#endif // INSTRUCTIONS_H

