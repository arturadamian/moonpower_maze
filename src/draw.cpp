#include "../headers/maze.h"

//draw vertical lines
void verLine(int x, int y1, int y2, const ColorRGB& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

/**
 * drawBackground - Draw the sky and floor
 * @instance: An SDL_Instance containing the window and renderer objects
 **/
void drawBackground(SDL_Renderer *renderer)
{
    int x;
    
    for (x = 0; x <= SCREEN_WIDTH; x++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0xDD, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT / 2);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0xFF, 0xFF);
        SDL_RenderDrawLine(renderer, x, SCREEN_HEIGHT / 2, x,
                           SCREEN_HEIGHT);
        
    }
    SDL_RenderPresent(renderer);
    
}

void drawRect(int x1, int y1, int x2, int y2, const ColorRGB& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect r = {x1, y1, x2-x1, y2-y1};
    SDL_RenderFillRect(renderer, &r);
    }
