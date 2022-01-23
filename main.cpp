#include <iostream>
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "functions.h"
#include "Classes.h"



#undef main

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;
extern LButtonPosition buttons[5];



int main()
{
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

					for (int i = 0; i < 5; ++i)
					{
						if (buttons[i].active)
						{
							buttons[i].HandleEvent(&e);
						}
					}

				}
				///Main Menu
				for (int i = 1; i <= 2; ++i)
					buttons[i].active = true;




				SDL_SetRenderDrawColor(Renderer, 121, 85, 72, 255);
				SDL_RenderClear(Renderer);
				SDL_RenderPresent(Renderer);
			}
		}
	}

	
}
