#pragma once
#include <iostream>
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "Classes.h"
#include <string>
#include <sstream>
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

LImage mainMenu, blackTrans, kastely, kastely_belso, hid, akasztott, halalSotet, gameOver, keseles, banyaBejar, goblin;
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
SDL_Rect textTransition5 = { 0, 0, 0, 15 };
SDL_Rect textTransition6 = { 0, 0, 0, 15 };


bool b_mainMenu, b_stage0, b_stage1, b_stage2, b_stage3, b_stage4;
bool b_stage_akasztas, b_stage_keseles;
bool dia[10];
Uint8 darkness;
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
    menuFont = TTF_OpenFont("prstart.ttf", 90);
    if (menuFont == NULL)
    {
        std::cout << TTF_GetError() << "\n";
        return false;
    }
    textFont = TTF_OpenFont("prstart.ttf", 15);
    if(textFont == NULL)
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
    if (!hid.loadFromFile("Images/goblin_hid.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!akasztott.loadFromFile("Images/hanging.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!halalSotet.loadFromFile("Images/death.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!gameOver.loadFromFile("Images/gameOver.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!keseles.loadFromFile("Images/keseles.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!banyaBejar.loadFromFile("Images/banya_bejarat.png"))
    {
        std::cout << IMG_GetError() << "\n";
        return false;
    }
    if (!goblin.loadFromFile("Images/goblin.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    ///Texts///
    SDL_Color textColor = {0, 0, 0};
    if (!mainMenuText.loadFromRenderedText("Save The Girl", textColor, menuFont))
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

void loadTextsStage0()
{
    if (!textBoxtext1.loadFromRenderedText("Once upon a time there was a well known", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("adventurer, you. You lived in the strong Assyrian", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("Empire along with your comrades whom you knew", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext4.loadFromRenderedText("very well, and vice versa.The same goes for the", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext5.loadFromRenderedText("walls, for every mouse hole, for every pub, for", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext5.loadFromRenderedText("for every hideout. Neither was the king an", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext6.loadFromRenderedText("exception.", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
    textTransition4 = { 0, 0, 0, 15 };
    textTransition5 = { 0, 0, 0, 15 };
    textTransition6 = { 0, 0, 0, 15 };
}

void changeDialogStage0()
{
    dia[0] = false;
    dia[1] = true;
    if(!textBoxtext1.loadFromRenderedText("He has entrusted you with a bunch of missions", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("throughout the years which you completed without", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("any problems.", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext4.loadFromRenderedText("One day the emperor called you in...", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
    textTransition4 = { 0, 0, 0, 15 };
}

void loadTextsStage1() //loads initial texts and sets other stuff
{
    if (!textBoxtext1.loadFromRenderedText("EMPEROR: You are probably wondering why I invited", { 158, 158, 158 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("you to my splendid palace! Unfortunately, my", { 158, 158, 158 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("daughter has been kidnapped!", { 158, 158, 158 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };

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
            if (!textBoxtext1.loadFromRenderedText("YOU: This is the fifth time this year...", { 158, 158, 158 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 2)
        {
            if (!textBoxtext1.loadFromRenderedText("EMPEROR: Therefore, I kindly ask you to", { 158, 158, 158 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            if (!textBoxtext2.loadFromRenderedText("help her.", { 158, 158, 158 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
            textTransition2 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 3)
        {
            if (!textBoxtext1.loadFromRenderedText("YOU: Where is she?", { 158, 158, 158 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            textTransition1 = { 0, 0, 0, 15 };
        }
        else if (i + 1 == 4)
        {
            if (!textBoxtext1.loadFromRenderedText("EMPEROR: Gossips say she is in the dangerous", { 158, 158, 158 }, textFont))
            {
                std::cout << TTF_GetError() << "\n";
            }
            if (!textBoxtext2.loadFromRenderedText("Magic Mine!", { 158, 158, 158 }, textFont))
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
    }
}

void loadTextsStage2()
{
    if (!textBoxtext1.loadFromRenderedText("On your way, you have met your", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("old friend, Gibbon the goblin...", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
}


void changeDialogStage2()
{
    int i;
    for (i = 0; i <= 3 && !dia[i]; ++i);

    dia[i] = false;
    dia[i + 1] = true;
    if (i + 1 == 1)
    {
        if (!textBoxtext1.loadFromRenderedText("GIBBON: So we meet again! You already know my", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("conditions: either you pay to cross this bridge", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("or you die!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 2)
    {
        if (!textBoxtext1.loadFromRenderedText("YOU: Weren't you under the the Emperor's ", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("protection, I would have killed you 10 times ", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("already!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 3)
    {
        if (!textBoxtext1.loadFromRenderedText("GIBBON: So what is your next move? (1/2)", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. Don't pay and try to escape.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("2. Pay.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
    }
}

void loadTextsStage_keseles()
{
    if (!textBoxtext1.loadFromRenderedText("He stabbed you 45 times with his butterknife", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("and you died a horrible death...", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("(press any key to restart)", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
}

void loadTextsStage_akasztas()
{
    if (!textBoxtext1.loadFromRenderedText("For you haven't completed the emperor's command", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("you have been hanged...(press any key to restart)", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };

}

void loadTextsStage3()
{
    if (!textBoxtext1.loadFromRenderedText("Now at the entrance of the mine you run", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("into a miner.", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
}

void changeDialogStage3()
{
    int i;
    for (i = 0; i <= 4 && !dia[i]; ++i);

    dia[i] = false;
    dia[i + 1] = true;

    if (i + 1 == 1)
    {
        if (!textBoxtext1.loadFromRenderedText("MINER: Halt! You shall not pass, unless ", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("you answer my question!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 2)
    {
        if (!textBoxtext1.loadFromRenderedText("YOU: I don't have any money on me, you", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("can ask Gibbon.", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 3)
    {
        if (!textBoxtext1.loadFromRenderedText("MINER: I don't care about your filthy money!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("My question is:", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("What is the integral of (x-2)/sqrt(1-x^2)?(1/2/3)", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("1. sqrt(1 - x^2) - 2 * x * arcsin(x) + c", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("2. sqrt(1 - x^2) - 2 * arcsin(x) + c", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext6.loadFromRenderedText("3. sqrt(1 - x) - 2 * x * arcsin(x) + c", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
        textTransition5 = { 0, 0, 0, 15 };
        textTransition6 = { 0, 0, 0, 15 };
    }
    if (i + 1 == 4)
    {
        if (!textBoxtext1.loadFromRenderedText("MINER: I won't let into my mine some stupid fool,", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("who cannot answer some rudimentary questions!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("Get the hell out of my sight!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
    }
}

int Time()
{
    return  startTime - SDL_GetTicks();
}

//ez a fekete transition eleinte felteszi az atlatszosagot 255 (full fekete);
//utana a main-ben fokozatosan csokkentsuk ez (egyre atlatszobb lesz) -> az illuzioja, hagy van atmenet
