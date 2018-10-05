#include "headers/maze.h"

/**
 * present - present what was drawn, update display
 */
void present()
{
    SDL_RenderPresent(renderer);
}

/**
 * clearScreen - clears screen to black
 */
void clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
