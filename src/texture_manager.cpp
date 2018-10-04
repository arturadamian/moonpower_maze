#include "../headers/maze.h"

//load texture
SDL_Texture* loadTexture(const char* texture)
{
    SDL_Surface* tmpSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    cout << "Surface loaded!" << endl;
    
    return tex;
}

//draw buffer of pixels to screen where size = # pixels on screen (SCREEN_WIDTH * SCREEN_HEIGHT)
void drawBuffer(Uint32* buffer, bool swapXY)
{
    if( swapXY )
    {
        // copy the entire buffer straight into the texture
        SDL_UpdateTexture(scr, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
    }
    else
    {
        for( int x = 0; x < SCREEN_WIDTH; ++x )
        {
            // the verticle line to be update on the target texture
            SDL_Rect vStripe;
            vStripe.x = x;
            vStripe.y = 0;
            vStripe.w = 1;
            vStripe.h = SCREEN_HEIGHT;
            
            // things get a bit tricksy here, i'm telling sdl the buffer is only 1 pixel wide
            SDL_UpdateTexture(scr, &vStripe, buffer, sizeof(Uint32));
            // then incrementing the buffer pointer to the next line of the beffer i.e. the next vStripe in the texture
            buffer += SCREEN_HEIGHT;
        }
    }
    // draw the entire texture to the screen
    SDL_RenderCopy(renderer, scr, NULL, NULL);
}

//make textures from colors
void generateTextures()
{
    for(int i = 0; i < 8; i++)
        textures[i].resize(texWidth * texHeight);
    
    for(int x = 0; x < texWidth; x++)
    {
        for(int y = 0; y < texHeight; y++)
        {
            int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
            int ycolor = y * 256 / texHeight;
            int xycolor = y * 128 / texHeight + x * 128 / texWidth;
            textures[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
            textures[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
            textures[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
            textures[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
            textures[4][texWidth * y + x] = 256 * xorcolor; //xor green
            textures[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
            textures[6][texWidth * y + x] = 65536 * ycolor; //red gradient
            textures[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
            
        }
    }
    ceilTexture = loadTexture("dependencies/images/aoa2.png");
}

//load background image
void loadBackground(SDL_Texture *src, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = 1200;
    dest.h= 600;
    
    clearScreen();
    SDL_RenderCopy(renderer, src, NULL, &dest);
    //redraw();
}
