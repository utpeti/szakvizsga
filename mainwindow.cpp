#include "mainwindow.h"
#include <iostream>
#include <SDL.h>

using namespace std;

void mainwindow()
{

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "VIDEO INIT HIBA!";
	else
	{
		window = SDL_CreateWindow("Szakvizsga program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN); //felbontast itt valtoztatunk
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); //kitoltom feherrel a feluletet
		SDL_UpdateWindowSurface(window);
		//SDL_Delay(5000);
	}
}

