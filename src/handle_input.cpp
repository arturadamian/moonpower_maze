#include "../headers/maze.h"

//uses scancode to listen for keyboard input
bool keyDown(SDL_Scancode key)
{
    return (inkeys[key] != 0);
}

//passes value of pressed keys to inkeys
void readKeys()
{
    inkeys = SDL_GetKeyboardState(NULL);
}

//move player
void movePlayer(double frameTime)
{
    //modify speed
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    readKeys();
    
    //move forward if no wall in front of you
    if (keyDown(SDL_SCANCODE_UP) || keyDown(SDL_SCANCODE_W))
    {
        //booster
        if (keyDown(SDL_SCANCODE_LSHIFT))
        {
            moveSpeed *= 2;
            rotSpeed *= 2;
        }
        if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
            posX += dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
            posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (keyDown(SDL_SCANCODE_DOWN) || keyDown(SDL_SCANCODE_S))
    {
        //booster
        if (keyDown(SDL_SCANCODE_LSHIFT))
        {
            moveSpeed *= 2;
            rotSpeed *= 2;
        }
        if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
            posX -= dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
            posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if (keyDown(SDL_SCANCODE_RIGHT) || keyDown(SDL_SCANCODE_D))
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (keyDown(SDL_SCANCODE_LEFT) || keyDown(SDL_SCANCODE_A))
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
}
