#include "../headers/maze.h"

using namespace std;
/**
 * init - prep screen for SDL2 instance
 *
 * @title: window title
 * @width: screen width, projection plane width
 * @height: screen height, projection plane height
 * @fullscreen: true for fullscreen, false for NO fullscreen display
 */

void init(const char* title, int width, int height)
{
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    
    if (SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) == 0)
    {
        cout << "SDL subsystems initialized!" << endl;
        
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);
        if (window)
        {
            cout << "Window created!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "Renderer created!" << endl;
        }
    }

    scr = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    addMusic("dependencies/audio/spooky.mp3");
    ceilTexture = loadTexture("dependencies/images/aoa2.png");
    
    generateTextures();
    
}
