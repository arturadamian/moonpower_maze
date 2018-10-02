#include "../headers/easycg.h"

namespace EasyCG
{

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    bool isRunning;
    SDL_Window*  window;
    SDL_Renderer* renderer;
    SDL_Texture* scr; // used in drawBuffer()

    const Uint8* inkeys;
    SDL_Event event = {0};
    
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

    /**
     * screen - prep screen for SDL2 instance
     *
     * @title: window title
     * @width: screen width, projection plane width
     * @height: screen height, projection plane height
     * @fullscreen: true for fullscreen, false for NO fullscreen display
     */
    void screen(const char* title, int width, int height, bool fullscreen)
    {
        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;

        int flags = 0;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        
        if (SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) == 0)
        {
            cout << "SDL subsystems initialized!" << endl;
            
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
            if (window)
            {
                cout << "Window created!" << endl;
            }
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                cout << "Renderer created!" << endl;
            }
            
            //SDL_Renderer *gRenderer = SDL_GetRenderer(window);
            
            
            //surface = SDL_GetWindowSurface(window);
            //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
            
           // wallTexture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

            
            
            

            //SDL_Texture* floorTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 1, SCREEN_HEIGHT);
    //        SDL_Texture* ceilTexture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_STREAMING, 1, SCREEN_HEIGHT);
            
            
    /*        SDL_RWops* rwop = SDL_RWFromFile("dependencies/images/snow.png", "rb"); //create RWops object from file, pointers to memory, load texture file
            SDL_Surface* loaded = IMG_LoadPNG_RW(rwop);
            SDL_Surface* conv = NULL;
            if (loaded)
            {
                conv = SDL_ConvertSurface(loaded, 0, 0);
                SDL_FreeSurface(loaded);
                cout << "Surface loaded!" << endl;
            }
     
            SDL_Surface* srf_floor = conv;
     
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, srf_floor);*/
            
            /*SDL_Texture* texture = loadTexture("dependencies/images/snow.png");
            
            
            SDL_Rect texture_rect;
            texture_rect.x = 1;  //the x coordinate
            texture_rect.y = 1; // the y coordinate
            texture_rect.w = 64; //the width of the texture
            texture_rect.h = 64; //the height of the texture
            
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
            SDL_RenderPresent(renderer); //updates the renderer*/
            // get window surface
    /*        gSurface = SDL_GetWindowSurface(window);
            if (gSurface)
            {
                cout << "Surface created!" << endl;
            }
     
            // create floor texture
            gFloorTexture = SDL_CreateTexture(renderer, gSurface->format->format,
                                              SDL_TEXTUREACCESS_STREAMING, 1, SCREEN_HEIGHT);
            if (gFloorTexture)
            {
                cout << "Floor texture created!" << endl;
            }
     
            // create ceiling texture
            gCeilTexture = SDL_CreateTexture(renderer, gSurface->format->format,
                                             SDL_TEXTUREACCESS_STREAMING, 1, SCREEN_HEIGHT);
            if (gCeilTexture)
            {
                cout << "Ceiling texture created!" << endl;
            }
     
            srf_ceil = loadSurface("dependencies/images/concrete_black.png");
            srf_floor = loadSurface("dependencies/images/snow.png");*/
            //isRunning = true;
        }
        //else
         //   isRunning = false;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //this is white
        scr = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        addMusic("dependencies/audio/spooky.mp3");

    }
    
    // present what was drawn, update display
    void redraw()
    {
        SDL_RenderPresent(renderer);
    }

    // prep for new render display
    void clearScreen(const ColorRGB& color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderClear(renderer);
    }
    
    //Scancodes don't move even if the user has a different keyboard layout
    bool keyDown(SDL_Scancode key)
    {
        return (inkeys[key] != 0);
    }
    
    // passes value of pressed keys to inkeys
    void readKeys()
    {
        inkeys = SDL_GetKeyboardState(NULL);
    }

    // listens for 'QUIT' event by user
    bool done()
    {
        SDL_Delay(5); //consumes less processing power
        readKeys();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return true;
            if (keyDown(SDL_SCANCODE_ESCAPE)) return true;
        }
        return false;
    }

    // ends program
    void end()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        cout << "Game cleaned!" << endl;
    }

    //draw vertical lines
    void verLine(int x, int y1, int y2, const ColorRGB& color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawLine(renderer, x, y1, x, y2);
    }

    
    ////////////////////////////////////////////////////////////////////////////////
    //Texture/////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    SDL_Texture* cropTexture (SDL_Texture* src, int x, int y)
    {
        SDL_Texture* dst = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 64, 64);
        SDL_Rect rect = {64 * x, 64 * y, 64, 64};
        SDL_SetRenderTarget(renderer, dst);
        SDL_RenderCopy(renderer, src, &rect, NULL);
        SDL_SetRenderTarget(renderer, NULL);
        
        return dst;
    }
    
    SDL_Texture* loadTexture(const char* texture)
    {
        SDL_Surface* tmpSurface = IMG_Load(texture);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        cout << "Surface loaded!" << endl;
        
        return tex;
    }

    /**
     * loadSurface - load surface
     *
     * @file: texture image
     * Return: converted surface prepped for texturing
     */
    SDL_Surface* loadSurface (const char * file)
    {
        SDL_RWops* rwop = SDL_RWFromFile(file, "rb"); //create RWops object from file, pointers to memory, load texture file
        SDL_Surface* loaded = IMG_LoadPNG_RW(rwop);
        SDL_Surface* conv = NULL;
        if (loaded)
        {
            conv = SDL_ConvertSurface(loaded, 0, 0);
            SDL_FreeSurface(loaded);
        }
        return conv;
    }
    
    

    /*SDL_Texture* loadImage(int gridNumber, unsigned long tw, unsigned long th, const char* texture)
    {
        SDL_Surface* tmpSurface = IMG_Load(texture);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        
        
    }*/
    
    /*remove later*/
    SDL_Texture* LoadTexture(const char* file)
    {
        SDL_Texture* newTexture = NULL;
        
        SDL_Surface* loadedSurface = IMG_Load(file);
        
        if (loadedSurface == NULL)
            printf("Unable to load the image %s! SDL_image Error: %s\n", file, IMG_GetError());
        else
        {
            newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            
            if (newTexture == NULL)
                printf("Unable to create the texture from %s! SDL Error: %s\n", file, SDL_GetError());
            
            SDL_FreeSurface(loadedSurface);
        }
        
        return newTexture;
    }

    //Draws a buffer of pixels to the screen
    //The number of elements in the buffer must equal the number of pixels on screen (width * height)
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
    

    void addMusic(const char* musicfile)
    {
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
        Mix_Music *music = Mix_LoadMUS(musicfile);
        Mix_PlayMusic(music, 3);
    }
} /*end EasyCG namespace*/
