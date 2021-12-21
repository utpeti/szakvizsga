#include "mainwindow.h"
#include <iostream>
#include <SDL.h>

using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* gXOut = NULL;

void mainwindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "VIDEO INIT HIBA!";
	else
	{
		window = SDL_CreateWindow("Szakvizsga program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN); //felbontast itt valtoztatunk
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); //kitoltom feherrel a feluletet
		SDL_UpdateWindowSurface(window);
		bool quit = false;
		SDL_Event e;
		while (!quit) //amig nem lepsz ki, fut
		{
			while (SDL_PollEvent(&e) != 0)
				if (e.type == SDL_QUIT)
					quit = true;
			SDL_BlitSurface(gXOut, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
		}
	}
}


