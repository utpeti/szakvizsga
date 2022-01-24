#pragma once
#include <iostream>
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "Classes.h"
/*#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>*/


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

const int MAX_BUTTONS = 2;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

LBackground kastely, kastely_belso, elag, banya, banyaelag; 

//textura gomboknak ezt a ket classt ossze lehetne tenni
LBackground buttonsTexture[5];

LButtonPosition buttons[5];

TTF_Font* gFont = NULL;

bool mainMenu, stage1;

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << SDL_GetError() << "\n";
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << SDL_GetError() << "\n";
        return false;
    }

    Window = SDL_CreateWindow("Szakvizsga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (Window == NULL)
    {
        std::cout << SDL_GetError() << "\n";
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL)
    {
        std::cout << SDL_GetError() << "\n";
        return false;
    }

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << TTF_GetError() << "\n";
        return false;
    }

    //initialize sdl mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)    //sound frequency(44100-standard), sample format
    {
                                                            //2 channels (stereo), chunksize (4096 for music) (minden hangnak a merete byte-ban: tul kicsi-kimarad, tul nagy-laggol)
        std::cout << Mix_GetError();
        return false;
    }

    return true;
   
}

bool loadMedia()
{
    ///Backgrounds
    if (!kastely.loadFromFile("Images/Kastely.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!kastely_belso.loadFromFile("Images/kastely_belso.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }

    ///button(s)
    if (!buttonsTexture[0].loadFromFile("Images/start.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    ///Characters///




    ///TTF letters///



    ///Button position///
    buttons[0].setPosition(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2); ///kozepen

    //buttons indexes
    for (int i = 0; i < MAX_BUTTONS; ++i)
        buttons[i].index = i;
    
    return true;
}
