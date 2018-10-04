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

/**
 * main - game loop
 *
 * Returns: 0
 */
int main(void)
{
    init("Attack on Arturs", 1200, 600);
    parseMap(worldMap);
    
    double time = 0; //current frame time
    double oldTime = 0; //previous frame time
    
    //game loop
    while(!quit())
    {
        drawTextureWalls();
        //drawColorWalls();
        redraw();
        //clearScreen(); // for color walls

        //update ticks
        oldTime = time;
        time = SDL_GetTicks(); 
        double frameTime = (time - oldTime) / 1000.0; //in seconds (not ms)
        //cout << (1.0 / frameTime) << endl; //FPS counter
        
        movePlayer(frameTime);
        loadBackground(ceilTexture, 0, 0);
    }
    close();
    return 0;
}
