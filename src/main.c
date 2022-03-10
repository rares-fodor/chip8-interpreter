#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "chip8.h"
#include "utils.h"

int main (int argc, char **argv) {
    chip8 chip8;
    load_rom(&chip8, "../../Tetris.ch8");

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    uint32_t *pixel_buff = malloc(sizeof(DISP_WIDTH * DISP_HEIGHT) * sizeof(uint32_t));
    SDL_Init(SDL_INIT_VIDEO);
    
    window = SDL_CreateWindow(
            "Chip8 Interpreter",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
        );
    if (!window) { error_handle("Couldn't create window!"); }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            0
        );
    if (!renderer) { error_handle("Couldn't create renderer!"); }

    texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            1280,
            720
        );
    if (!texture) { error_handle("Couldn't create texture!"); }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    int pitch = DISP_WIDTH * sizeof(chip8.display_mem[0]);
    SDL_UpdateTexture(texture, NULL, pixel_buff, pitch);

    return 0;
}
