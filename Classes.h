#pragma once
#include <iostream>
#include "../SDL2/include/SDL.h"
#include "../SDL2/SDL2_Image/include/SDL_image.h"
#include "../SDL2/SDL2_mixer/include/SDL_mixer.h"
#include "../SDL2/SDL2_ttf/include/SDL_ttf.h"
#include "functions.h"


extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

class LBackground
{
public:

	LBackground();

	~LBackground();

	void free();

	bool loadFromFile(std::string path);

private:

	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

LBackground::LBackground()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LBackground::~LBackground()
{
	free();
}

void LBackground::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0; 
		mHeight = 0;
	}
}

bool LBackground::loadFromFile(std::string path)
{
	//get rid of pre existing texture
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		
		return false;
	}

	newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
	if (newTexture == NULL)
	{
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return true;
}
