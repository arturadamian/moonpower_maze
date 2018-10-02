#ifndef __EASYCG_H__
#define __EASYCG_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>


using namespace std;

namespace EasyCG
{

    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
    extern SDL_Window*   window;
    extern SDL_Renderer* renderer;
    extern SDL_Surface* surface;
    extern SDL_Texture* wallTexture;
    //SDL_Renderer *gRenderer;
    

    struct ColorRGB
    {
      int r;
      int g;
      int b;
      
      ColorRGB(Uint8 r, Uint8 g, Uint8 b);
      ColorRGB();
    };

    ColorRGB operator/(const ColorRGB& color, int a);

    static const ColorRGB RGB_Black    (  0,   0,   0);
    static const ColorRGB RGB_Red      (255,   0,   0);
    static const ColorRGB RGB_Green    (  0, 255,   0);
    static const ColorRGB RGB_Blue     (  0,   0, 255);
    static const ColorRGB RGB_Cyan     (  0, 255, 255);
    static const ColorRGB RGB_Magenta  (255,   0, 255);
    static const ColorRGB RGB_Yellow   (255, 255,   0);
    static const ColorRGB RGB_White    (255, 255, 255);
    static const ColorRGB RGB_Gray     (128, 128, 128);
    static const ColorRGB RGB_Grey     (192, 192, 192);
    static const ColorRGB RGB_Maroon   (128,   0,   0);
    static const ColorRGB RGB_Darkgreen(  0, 128,   0);
    static const ColorRGB RGB_Navy     (  0,   0, 128);
    static const ColorRGB RGB_Teal     (  0, 128, 128);
    static const ColorRGB RGB_Purple   (128,   0, 128);
    static const ColorRGB RGB_Olive    (128, 128,   0);

    void screen(const char* title, int width, int height, bool fullscreen); //initialize screen
    void redraw();                                              // updates display
    void clearScreen(const ColorRGB& color = RGB_Black);        // clears screen to black
    bool keyDown(SDL_Scancode key);     // checks if key is pressed
    void readKeys();             // gets current keyboard input state
    bool done();                //listens for QUIT event
    void end();                  // free memory
    void addMusic(const char* musicfile);
    void drawBuffer(Uint32* buffer, bool swapXY = false);       // Draws an array of (w * h) pixel data to the screen
    inline unsigned long getTicks() { return SDL_GetTicks(); }  // milliseconds since SDL was initialised
    inline double getTime() { return SDL_GetTicks() / 1000.0; } // seconds since SDL was initialised

    void verLine(int x, int y1, int y2, const ColorRGB& color); // draws a verticle line
    
    ////////////////////////////////////////////////////////////////////////////////
    //Textures/////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    SDL_Texture* cropTexture (SDL_Texture* src, int x, int y); // crop texture
    SDL_Texture* loadTexture(const char* texture);   //load texture
    SDL_Texture* loadImage(vector<Uint32> gridNumber, unsigned long tw, unsigned long th, const char* texture);
    SDL_Surface* loadSurface (const char * file);
    SDL_Texture* LoadTexture(const char* file);
    void loadFile(vector<unsigned char>& buffer, const char* filename);
    //SDL_Surface* loadSurface (const char * file);

}

#endif /*__EASYCG_H__*/
