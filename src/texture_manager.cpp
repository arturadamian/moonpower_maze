#include "headers/maze.h"

/**
 * loadTextures - load textures
 */
void loadTextures()
{
    SDL_Surface *textures[numTex]; //store textures to be loaded
    
    //load images
    textures[0] = IMG_Load("dependencies/images/nightsky64.png");
    textures[1] = IMG_Load("dependencies/images/kitty64.png");
    textures[2] = IMG_Load("dependencies/images/artur_64.png");
    textures[3] = IMG_Load("dependencies/images/sm_color.png");
    textures[4] = IMG_Load("dependencies/images/mercury_color.png");
    textures[5] = IMG_Load("dependencies/images/venus_color.png");
    textures[6] = IMG_Load("dependencies/images/jupiter_color.png");
    textures[7] = IMG_Load("dependencies/images/mars_color.png");
    textures[8] = IMG_Load("dependencies/images/crystal64.png");

    //get texture pixels and store in array
    for (int i = 0; i < numTex; i++)
    {
        for (int j = 0; j < texHeight; j++)
        {
            for (int k = 0; k < texWidth; k++)
            {
                //use bit manipulation to store pixel color
                pixel = (uint8_t *)textures[i]->pixels + k * textures[i]->pitch + j * textures[i]->format->BytesPerPixel;
                aTexture[i][j][k] = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            }
        }
    }
    
    //free each texture surface in array
    for (int i = 0; i < numTex; i++)
    {
        SDL_FreeSurface(textures[i]);
        textures[i] = NULL;
    }
}

/**
 * drawBuffer - draw buffer of pixel data onto screen where
 * buffersize = total # pixels on screen (SCREEN_WIDTH * SCREEN_HEIGHT)
 *
 * @buffer: buffer of pixel data
 */

void drawBuffer(uint32_t* buffer)
{
    // copy entire buffer onto screen
    SDL_UpdateTexture(screen, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
    
    // draw the entire texture to the screen
    SDL_RenderCopy(renderer, screen, NULL, NULL);
}


