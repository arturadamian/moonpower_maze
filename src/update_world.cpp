#include "../headers/maze.h"


// present what was drawn, update display
void redraw()
{
    SDL_RenderPresent(renderer);
}

// prep for new render display
void clearScreen(const ColorRGB& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderClear(renderer);
}
