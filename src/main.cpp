#include "headers/maze.h"
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
    init("Moonpower Maze", 1200, 600);
    parseMap();
    
    double currTime = 0; //current frame time
    double prevTime = 0; //previous frame time
    
    //game loop
    while(!quit())
    {
        drawPicWalls();
        present();
        
        //update ticks
        prevTime = currTime;
        currTime = SDL_GetTicks();
        double frameTime = (currTime - prevTime) / 1000.0; //in seconds
        
        movePlayer(frameTime);
    }
    close();
    return 0;
}
