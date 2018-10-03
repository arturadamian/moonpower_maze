#include "../headers/maze.h"

// listens for 'QUIT' event by user
bool done()
{
    SDL_Delay(5); //consumes less processing power
    readKeys();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) return true;
        if (keyDown(SDL_SCANCODE_ESCAPE)) return true;
    }
    return false;
}

// ends program
void end()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    cout << "Game cleaned!" << endl;
}
