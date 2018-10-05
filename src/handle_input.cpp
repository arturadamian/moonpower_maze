#include "headers/maze.h"

/**
 * movePlayer - enable player to rotate and move forward/backwards
 *
 * @frameTime: frames per second
 */
void movePlayer(double frameTime)
{
    //modify player move and turn speed
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    
    getKeyState(); //get keyboard state
    
    //move forward if no wall in front
    if (pressed(SDL_SCANCODE_UP) || pressed(SDL_SCANCODE_W))
    {
        if (int(posX) == exX && int(posY) == exY)
            switch_map = 1;

        //booster
        if (pressed(SDL_SCANCODE_LSHIFT))
        {
            moveSpeed *= 2;
            rotSpeed *= 2;
        }
        if (switch_map == 0)
        {
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
                posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
                posY += dirY * moveSpeed;
        }
        else
        {
            if(world2Map[int(posX + dirX * moveSpeed)][int(posY)] == false)
                posX += dirX * moveSpeed;
            if(world2Map[int(posX)][int(posY + dirY * moveSpeed)] == false)
                posY += dirY * moveSpeed;
        }
                
    }
    
    //move backwards if no wall behind
    if (pressed(SDL_SCANCODE_DOWN) || pressed(SDL_SCANCODE_S))
    {
        if (int(posX) == exX && int(posY) == exY)
            switch_map = 1;
        //booster
        if (pressed(SDL_SCANCODE_LSHIFT))
        {
            moveSpeed *= 2;
            rotSpeed *= 2;
        }
        if (switch_map == 0)
        {
            if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
                posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
                posY -= dirY * moveSpeed;
        }
        else
        {
            if(world2Map[int(posX - dirX * moveSpeed)][int(posY)] == false)
                posX -= dirX * moveSpeed;
            if(world2Map[int(posX)][int(posY - dirY * moveSpeed)] == false)
                posY -= dirY * moveSpeed;
        }
    }
    
    //rotate right
    if (pressed(SDL_SCANCODE_RIGHT) || pressed(SDL_SCANCODE_D))
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    
    //rotate left
    if (pressed(SDL_SCANCODE_LEFT) || pressed(SDL_SCANCODE_A))
    {
        //both camera direction and camera plane must be rotated
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
    
    //stop and resume music
    if (pressed(SDL_SCANCODE_MINUS))
            Mix_PauseMusic();
    if (pressed(SDL_SCANCODE_EQUALS))
            Mix_ResumeMusic();
}
