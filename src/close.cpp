#include "headers/maze.h"

/**
 * quit - listens for 'QUIT' event or pressed 'escape' key by user
 */
bool quit()
{
    getKeyState();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || pressed(SDL_SCANCODE_ESCAPE))
            return true;
    }
    return false;
}

/**
 * close - free memory
 */
void close()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    if (texture)
        SDL_DestroyTexture(texture);
        
    SDL_Quit();
    cout << "Game cleaned!" << endl;
}
