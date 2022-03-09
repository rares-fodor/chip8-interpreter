#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "chip8.h"

int main (int argc, char **argv) {
    chip8 chip8;
    load_rom(&chip8, "Betris.ch8");

    
    return 0;
}
