#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h> //eddig az alap dolgok vannak incudeolva, talan nehany folosben van (a modularis programozas miatt), checkold kesobb
#include "mainwindow.h" //ez az ablak generator header fajlja (crtl + click <3)

#undef main

int main()
{
	mainwindow();
}