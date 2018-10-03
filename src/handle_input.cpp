#include "../headers/maze.h"


//Scancodes don't move even if the user has a different keyboard layout
bool keyDown(SDL_Scancode key)
{
    return (inkeys[key] != 0);
}

// passes value of pressed keys to inkeys
void readKeys()
{
    inkeys = SDL_GetKeyboardState(NULL);
}

