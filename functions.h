#pragma once
#include <iostream>
#include <SDL.h>
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

LImage mainMenu, blackTrans, kastely, kastely_belso, hid, akasztott, halalSotet, gameOver, keseles, banyaBejar, banyaBelso, black, asthma;
LImage textBox;
LImage textBoxtext1, textBoxtext2, textBoxtext3, textBoxtext4, textBoxtext5, textBoxtext6, textBoxtext7;
LImage mainMenuText;
LImage mero[6];

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


bool b_mainMenu, b_stage0, b_stage1, b_stage2, b_stage3, b_stage4, b_stage5, b_stage6, b_stage7;
bool b_stage_akasztas, b_stage_keseles, b_stage_asthma;
bool dia[20];
Uint8 darkness;
int startTime;
unsigned int meroindex = 1;

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
    if (!banyaBelso.loadFromFile("Images/banya_belso.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!black.loadFromFile("Images/black.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!asthma.loadFromFile("Images/asthma.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[1].loadFromFile("Images/meroke.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[2].loadFromFile("Images/meroke2.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[3].loadFromFile("Images/meroke3.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[4].loadFromFile("Images/meroke4.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[5].loadFromFile("Images/meroke5.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    if (!mero[6].loadFromFile("Images/meroke6.png"))
    {
        std::cout << IMG_GetError() << "\n";
    }
    ///Texts///
    SDL_Color textColor = { 0, 0, 0 };
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
    if (!textBoxtext1.loadFromRenderedText("He has entrusted you with a bunch of missions", { 200, 200, 200 }, textFont))
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

void loadTextsStage4()
{
    if (!textBoxtext1.loadFromRenderedText("You managed to enter a mine...good job!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("Everyone is proud of you. Ohh..You've got a", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("torch too. You are getting better, champ!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext4.loadFromRenderedText("Press E to light your torch...", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
    textTransition4 = { 0, 0, 0, 15 };
}

void loadTextsStage5()
{
    if (!textBoxtext1.loadFromRenderedText("It seems to be a junction. You choose the path:", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("1. On the left", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("2. In the middle", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext4.loadFromRenderedText("3. On the right", { 255, 255, 255 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
    textTransition4 = { 0, 0, 0, 15 };
}

void loadTextsStage6_1()
{
    if (!textBoxtext1.loadFromRenderedText("After a prolonged walk you arrive to the mighty", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("glorious noble wise Supreme Leader's daughter.", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
}

void loadTextsStage6_2()
{
    if (!textBoxtext1.loadFromRenderedText("You've arrived easily to the Emperor's daughter.", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("Luckily you've picked the best possible path.", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
}

void changeDialogStage6()
{
    dia[0] = false;
    dia[1] = true;
    if (!textBoxtext1.loadFromRenderedText("Entering into the depths of the cave you notice", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText("the girl crying on a rock. You look around and", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText("find no monster, no burglar, no final boss which", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext4.loadFromRenderedText("you could fight with. Nevertheless, you are", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext5.loadFromRenderedText("precautious, and slowly approach her:", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
    textTransition4 = { 0, 0, 0, 15 };
    textTransition5 = { 0, 0, 0, 15 };
}

void loadTextsStage7()
{
    if (!textBoxtext1.loadFromRenderedText("YOU: Excuse me Miss! There is no need to be", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext2.loadFromRenderedText(" devastated anymore! I came here for your rescue,", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    if (!textBoxtext3.loadFromRenderedText(" just kindly tell me where is you kidnapper!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
    }
    textTransition1 = { 0, 0, 0, 15 };
    textTransition2 = { 0, 0, 0, 15 };
    textTransition3 = { 0, 0, 0, 15 };
}

void changeDialogStage7()
{
    int i;
    for (i = 0; i <= 10 && !dia[i]; ++i);

    dia[i] = false;
    dia[i + 1] = true;
    if(i + 1 == 1)
    {
        if (!textBoxtext1.loadFromRenderedText("PRINCESS: If you came here to bring me back", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("there, you can already get lost! There is no", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("terrifying monster here, I came here on my own.", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 2)
    {
        if (!textBoxtext1.loadFromRenderedText("YOU: What about the miner?", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
    }
    else if(i + 1 == 3)
    {
        if (!textBoxtext1.loadFromRenderedText("PRINCESS: I payed him to defend me and let in", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("only those people that have an IQ level above", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("room temperature. You know, I need a company", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("sometimes. But not with those jerk servants,", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("they know nothing!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
        textTransition5 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 4)
    {
        if (!textBoxtext1.loadFromRenderedText("Anyway...why did you come here?", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. The Emperor sent me", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("2. I was just being around", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("3. Beacuse of the reward", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 5)
    {
        if (!textBoxtext1.loadFromRenderedText("Why do you help for my father?", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. For the reward", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("2. I know you since you have born, I had to help", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("3. I have been given an order.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }

        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
    }
    if (i + 1 == 6)
    {
        if (!textBoxtext1.loadFromRenderedText("Please, leave me alone!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. You know I can't do that, Miss...It's my duty", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("to return you to the Emperor.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("2. I beg you, you can't stay here forever, Miss!", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("3. Without you? Never", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
        textTransition5 = { 0, 0, 0, 15 };
    }
    if (i + 1 == 7)
    {
        if (!textBoxtext1.loadFromRenderedText("...You don't know what will wait for me when", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("I arrive home. You just execute his tasks you", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("do not know him!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("1. It's still better in the castle", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("2. You need a hero, who saves you, and that's me", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext6.loadFromRenderedText("3. I will be there for you whatever happens!", { 255, 255, 255 }, textFont))
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
    if (i + 1 == 8)
    {
        if (!textBoxtext1.loadFromRenderedText("Why should I even trust you?", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. I've come all this way, at least come with me", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("already.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("2. We've known eachother since birth, you have", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("never been dissapointed by me.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext6.loadFromRenderedText("3. You can always trust me!", { 255, 255, 255 }, textFont))
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
    if (i + 1 == 9)
    {
        if (!textBoxtext1.loadFromRenderedText("Look, I really don't want to go back!", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. You will come back, doesn't matter if you want", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("to or not, Miss.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("2. You have to. Otherwise both of us will die.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext5.loadFromRenderedText("3. I have an offer for you", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
        textTransition5 = { 0, 0, 0, 15 };
    }
    else if (i + 1 == 10)
    {
        if (!textBoxtext1.loadFromRenderedText("If you come back with me:", { 200, 200, 200 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext2.loadFromRenderedText("1. I will marry you.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext3.loadFromRenderedText("2. I will kill your wicked father.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        if (!textBoxtext4.loadFromRenderedText("3. I will talk to your father.", { 255, 255, 255 }, textFont))
        {
            std::cout << TTF_GetError() << "\n";
        }
        textTransition1 = { 0, 0, 0, 15 };
        textTransition2 = { 0, 0, 0, 15 };
        textTransition3 = { 0, 0, 0, 15 };
        textTransition4 = { 0, 0, 0, 15 };
    }
}
/*
void changeDialogStage7_answer1()
{
    if (!textBoxtext1.loadFromRenderedText("I should have known...", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer2()
{
    if (!textBoxtext1.loadFromRenderedText("Liar!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer3()
{
    if (!textBoxtext1.loadFromRenderedText("Get out of here!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer4()
{
    if (!textBoxtext1.loadFromRenderedText("Get out of here!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer5()
{
    if (!textBoxtext1.loadFromRenderedText("I order you to go!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer6()
{
    if (!textBoxtext1.loadFromRenderedText("I can do whatever I want!", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
void changeDialogStage7_answer7()
{
    if (!textBoxtext1.loadFromRenderedText("^-^", { 200, 200, 200 }, textFont))
    {
        std::cout << TTF_GetError() << "\n";
        textTransition1 = { 0, 0, 0, 15 };
    }
}
*/
int Time()
{
    return  startTime - SDL_GetTicks();
}

//ez a fekete transition eleinte felteszi az atlatszosagot 255 (full fekete);
//utana a main-ben fokozatosan csokkentsuk ez (egyre atlatszobb lesz) -> az illuzioja, hagy van atmenet
