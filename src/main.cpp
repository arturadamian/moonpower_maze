#include "../headers/maze.h"
#include "draw.cpp"
#include "handle_input.cpp"
#include "texture_manager.cpp"
#include "close.cpp"
#include "window.cpp"
#include "effects.cpp"
#include "draw_walls.cpp"
#include "update_world.cpp"
#include "map_parser.cpp"


int main(void)
{
    init("Attack on Arturs", 1200, 600);
    parseMap(worldMap);
    
    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame
    
    //game loop
    while(!done())
    {
        drawWalls();

        //clearScreen();
        
        //update ticks
        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
        cout << (1.0 / frameTime) << endl; //FPS counter
        
        redraw();
        movePlayer(frameTime);
        
        // Clear the renderer
        SDL_RenderClear(renderer);
        
        // Render the image
        SDL_RenderCopy(renderer, ceilTexture, NULL, NULL);
        
        // Show the final render
        //SDL_RenderPresent(renderer);
    }
    close();
    return 0;
}

