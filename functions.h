#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Classes.h"
#include <string>
#include <sstream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 100;

const int MAX_BUTTONS = 2;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

LImage mainMenu, blackTrans, kastely, kastely_belso, elag, banya, banyaelag;
LImage textBox;
LImage textBoxtext1, textBoxtext2, textBoxtext3, textBoxtext4, textBoxtext5, textBoxtext6, textBoxtext7;
LImage mainMenuText;


//textura gomboknak ezt a ket classt ossze lehetne tenni
LButtonPosition buttons[5];

TTF_Font* menuFont = NULL;
TTF_Font* textFont = NULL;

//ezeken keresztul valosul meg a potyoges illuzioja, mutatja mennyi toltodjon be a szovegbol az utolso a height - > beolti a teljes betut nem vagja le a felet
SDL_Rect textTransition1 = { 0, 0, 0, 15 };
SDL_Rect textTransition2 = { 0, 0, 0, 15 };
SDL_Rect textTransition3 = { 0, 0, 0, 15 };
SDL_Rect textTransition4 = { 0, 0, 0, 15 };

bool b_mainMenu, b_stage0, b_stage1, b_stage2;
bool dia[10];
Uint8 darkness = 255;
int startTime;

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

    startTime = SDL_GetTicks();

    return true;

}

bool loadMedia()
{
    
    ///TTF fonts///
    menuFont = TTF_OpenFont("prstart.ttf", 100);
    if (menuFont == NULL)
    {
        std::cout << TTF_GetError() << "\n";
        return false;
    }
    textFont = TTF_OpenFont("prstart.ttf", 15);
    if (textFont == NULL)
    {
        std::cout << TTF_GetError() << "\n";
        return false;
    }
    
    ///Backgrounds
    if (!textBox.loadFromFile("Images/text_box.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    textBox.setAlpha(130);
    if (!blackTrans.loadFromFile("Images/black_transition.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!mainMenu.loadFromFile("Images/main_menu_hatter.png"))
    {
        std::cout << IMG_GetError() << "\n";
       return false;
    }
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
    ///Texts///
    SDL_Color textColor = { 0, 0, 0 };
    if (!mainMenuText.loadFromRenderedText("Sex The Game", textColor, menuFont))
    {
        std::cout << TTF_GetError() << "\n";
        return false;
    }


    ///button(s)
    if (!buttons[0].loadFromFile("Images/start.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    ///Characters///







    ///Button position///
    buttons[0].setPosition(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2); ///kozepen

    //buttons indexes
    for (int i = 0; i < MAX_BUTTONS; ++i)
        buttons[i].index = i;
        
    return true;
}

void loadTextsStage1() //loads initial texts
{
    if (!textBoxtext1.loadFromRenderedText("Emperor: You are probably wondering why I invited", { 0, 0, 0 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("you to my splendid palace! Unfortunately, my", { 0, 0, 0 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("daughter has been kidnapped!", { 0, 0, 0 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
}

void changeDialogStage1()
{
    int i;
    for (i = 0; i <= 3 && !dia[i]; ++i);

    if (i <= 3)
    {
        dia[i] = false; //a volt dialogus false - > torlodik
        dia[i + 1] = true;  //bejon az ujabb dialogus, amit most ezutan be load-olunks
        if (i + 1 == 1) //i + 1 a kovetkezo dia sorszama
        {
            if (!textBoxtext1.loadFromRenderedText("You: This is the fifth time this year...", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 2)
        {
            if (!textBoxtext1.loadFromRenderedText("Emperor: Therefore, I kindly please you to", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            if (!textBoxtext2.loadFromRenderedText("help her.", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
            textTransition2 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 3)
        {
            if (!textBoxtext1.loadFromRenderedText("You: Where is she?", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 4)
        {
            if (!textBoxtext1.loadFromRenderedText("Empereror: Gossips say she is in", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            if (!textBoxtext2.loadFromRenderedText("the dangerous Magic Mine!", { 0, 0, 0 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            if (!textBoxtext3.loadFromRenderedText("So, do you accept the mission? (y/n)", { 255, 255, 255 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
            textTransition2 = { 0, 0, 0, 15 };
            textTransition3 = { 0, 0, 0, 15 };
        }



    }/*
    else ->mivel a vegen mindig kell donteni, ide ez nem tehetjuk
    {
        b_stage1 = false;
        b_stage2 = true;
    }
    */
}

int Time()
{
    return  startTime - SDL_GetTicks();
}
//ez a fekete transition eleinte felteszi az atlatszosagot 255 (full fekete);
//utana a main-ben fokozatosan csokkentsuk ez (egyre atlatszobb lesz) -> az illuzioja, hagy van atmenet