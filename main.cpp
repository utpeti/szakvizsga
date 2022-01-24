#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "functions.h"
#include "Classes.h"
#include <iostream>

using namespace std;


//#undef main

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern LButtonPosition buttons[5];
extern bool mainMenu, stage1;


int main()
{
	mainMenu = true;
	if (init())
	{
		if (loadMedia())
		{

			bool quit = false;
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					if (mainMenu)
					{
						for (int i = 0; i < 2; ++i)
						{
							buttons[i].HandleEvent(&e);
						}
					}

				}

				///Cleaning
				SDL_SetRenderDrawColor(Renderer, 121, 85, 72, 255);
				SDL_RenderClear(Renderer);
				
				///Main Menu
				//To do: gomb aktivalas, hatter, szoveg
				if (mainMenu)
				{
					
					buttonsTexture[0].render(buttons[0].getPosx(), buttons[0].getPosy(), NULL);
					
				}
				else if (stage1)
				{
					kastely_belso.render(0, 0, NULL);
				}
				//else if

				
				SDL_RenderPresent(Renderer);

				
				
				
			}
		}
	}

	
}
