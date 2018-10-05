#ifndef __MAZE_H__
#define __MAZE_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#define mapWidth 24   //define constants for map dimensions, otherwise error
#define mapHeight 24
#define texWidth 64
#define texHeight 64

using namespace std;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

SDL_Window*  window;
SDL_Renderer* renderer;
SDL_Texture* scr; // used in drawBuffer()
SDL_Texture* ceilTexture;
SDL_Texture* texture;
vector<Uint32> textures[8];
const Uint8* inkeys;
SDL_Event event = {0};

double posX = 22, posY = 4;  //player x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //camera plane
int exX = 5, exY = 8;
int switch_map = 0;

int worldMap[mapWidth][mapHeight];
int world2Map[mapWidth][mapHeight];

struct ColorRGB
{
    int r;
    int g;
    int b;
    
    ColorRGB(Uint8 r, Uint8 g, Uint8 b);
    ColorRGB();
};

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

ColorRGB::ColorRGB()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

//Divides a color through an integer
ColorRGB operator/(const ColorRGB& color, int a)
{
    if(a == 0) return color;
    ColorRGB c;
    c.r = color.r / a;
    c.g = color.g / a;
    c.b = color.b / a;
    return c;
}

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

void init(const char* title, int width, int height);
void redraw();
void clearScreen(const ColorRGB& color = RGB_Black);     //clears screen to black by default
bool keyDown(SDL_Scancode key);
void readKeys();
bool quit();
void close();
void addMusic(const char* musicfile);
void drawBuffer(Uint32* buffer, bool swapXY = false); // draws an array of (w * h) pixel data to the screen
void verLine(int x, int y1, int y2, const ColorRGB& color);
SDL_Texture* loadTexture(const char* texture);
void loadBackground(SDL_Texture *src, int x, int y);
void generateTextures();
void parseMap(int worldMap[mapWidth][mapHeight]);
void movePlayer(double frameTime);
void drawTextureWalls();
void drawColorWalls();
#endif /*__MAZE_H__*/
