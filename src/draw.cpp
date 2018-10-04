#include "../headers/maze.h"

//draw vertical lines
void verLine(int x, int y1, int y2, const ColorRGB& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}
