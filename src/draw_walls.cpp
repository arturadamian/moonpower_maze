#include "../headers/maze.h"

void drawWalls()
{
    Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    for(int x = 0; x < SCREEN_WIDTH; x++)
    {
        //calculate ray position and direction
        double cameraX = 2 * x / double(SCREEN_WIDTH) - 1; //x-coordinate in camera space
        //double rayPosX = posX;
        //double rayPosY = posY;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;
        
        //which box of the map we're in
        int mapX = int(posX);
        int mapY = int(posY);
        
        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;
        
        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = abs(1 / rayDirX);
        double deltaDistY = abs(1 / rayDirY);
        double perpWallDist;
        
        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        
        int hit = 0; //was there a wall hit?
        int side = 0; //was a NS or a EW wall hit?
        
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        
        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        
        //Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if(drawEnd >= SCREEN_HEIGHT)drawEnd = SCREEN_HEIGHT - 1;
        
        //choose wall color
        /*ColorRGB color;
        switch(worldMap[mapX][mapY])
        {
            case 1:  color = RGB_Red;  break; //red
            case 2:  color = RGB_Green;  break; //green
            case 3:  color = RGB_Blue;   break; //blue
            case 4:  color = RGB_White;  break; //white
            default: color = RGB_Yellow; break; //yellow
        }
        
        //give x and y sides different brightness
        if (side == 1) {color = color / 2;}
        
        //draw the pixels of the stripe as a vertical line
        verLine(x, drawStart, drawEnd, color);*/
        //texturing calculations
        
        //texturing calculations
        int texNum = worldMap[mapX][mapY] + 2; //1 subtracted from it so that texture 0 can be used!
        
        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 0)
            wallX = posY + perpWallDist * rayDirY;
        else
            wallX = posX + perpWallDist * rayDirX;
        wallX -= (int)wallX;
        
        //x coordinate on the texture
        int texX = int(wallX * double(texWidth));
        if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
        
        for(int y = drawStart; y < drawEnd; y++)
        {
            int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            // TODO: avoid the division to speed this up
            int texY = ((d * texHeight) / lineHeight) / 256;
            Uint32 color = textures[texNum][texHeight * texY + texX];
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1) color = (color >> 1) & 8355711;
            buffer[y][x] = color;
        }
    }
    drawBuffer(buffer[0], true);
    for(int x = 0; x < SCREEN_WIDTH; x++)
        for(int y = 0; y < SCREEN_HEIGHT; y++)
            buffer[y][x] = 0;
}
