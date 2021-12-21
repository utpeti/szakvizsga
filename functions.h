#ifndef functions_h
#define functions_h


#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

SDL_Window* Window = 0;
SDL_Renderer* Renderer = 0;

const int WIDTH = 1280;
const int HEIGHT = 720;

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << SDL_GetError();
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        cout << SDL_GetError();
        return false;
    }

    Window = SDL_CreateWindow("Szakvizsga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (Window == NULL)
    {
        cout << SDL_GetError();
        return false;
    }

    SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL)
    {
        cout << SDL_GetError();
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << SDL_GetError();
        return false;
    }

    //initialize sdl mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)    //sound frequency(44100-standard), sample format
    {                                                            //2 channels (stereo), chunksize (4096 for music) (minden hangnak a merete byte-ban: tul kicsi-kimarad, tul nagy-laggol)
        cout << SDL_GetError();
        return false;
    }

    return true;

}

#endif