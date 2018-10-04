#include "../headers/maze.h"

// listens for 'QUIT' event or escape key by user
bool quit()
{
    readKeys();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || keyDown(SDL_SCANCODE_ESCAPE))
            return true;
    }
    return false;
}

// free memory
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
